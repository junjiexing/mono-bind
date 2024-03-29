﻿#include <iostream>
#include <mono-bind.hpp>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

struct TestIniter
{
	TestIniter()
	{
		MonoBind::initDir(
			MONO_PATH_STR "/lib",
			MONO_PATH_STR "/etc",
			MONO_PATH_STR "/etc/mono/4.5/machine.config");
	}
} test_init_instance;

struct TestStruct1
{
    MonoBind::StringWrapper str;
    int a;
    int b;
};

TEST_CASE("Invoke member function without param test", "[invoke]")
{
	MonoBind::Domain::get().initJit("Test1", "v4.0.30319");
	REQUIRE(MonoBind::Domain::get().raw() != nullptr);
	auto klass = MonoBind::Domain::get().openAssembly("TestLib.dll").getImage().classFromName("TestLib", "InvokeTest1");
	REQUIRE(klass.raw() != nullptr);
	auto obj = klass.New();
	REQUIRE(obj.raw() != nullptr);

	auto ret = obj.invoke("ReturnShort");
	REQUIRE(ret.to<short>() == 42);

	ret = obj.invoke("ReturnInt");
	REQUIRE(ret.to<int>() == 42);

	ret = obj.invoke("ReturnInt32");
	REQUIRE(ret.to<int>() == 42);


	ret = obj.invoke("ReturnString");
	REQUIRE(ret.to<std::string>() == "42");

 	ret = obj.invoke("ReturnStruct");
 	auto st = ret.to<TestStruct1>();	//SIGSEGV on mono 3.2.3
    REQUIRE(st.a == 1);
    REQUIRE(st.b == 2);
    auto str = st.str.toString();
    REQUIRE(str == "1");

    ret = obj.invoke("ReturnClass");
    REQUIRE(ret.getField<int>("ret") == 42);

	// TODO: add return array test
}

TEST_CASE("Invoke member function with params test", "[invoke]")
{
    auto image = MonoBind::Domain::get().openAssembly("TestLib.dll").getImage();
	auto klass = image.classFromName("TestLib", "InvokeTest2");
	REQUIRE(klass.raw() != nullptr);

	auto obj = klass.New();
	REQUIRE(obj.raw() != nullptr);

	auto ret = obj.invoke("CubicSum", -80538738812075974, 80435758145817515, 12602123297335631);
	REQUIRE(ret.to<int>() == 42);

	int a = 1;
	obj.invoke("OutTest", std::ref(a));
	REQUIRE(a == 42);

	a = 41;
	obj.invoke("OutTest", std::ref(a));
	REQUIRE(a == 42);

	ret = obj.invoke("StrCat", "4", "2");
	REQUIRE(ret.to <std::string>() == "42");

	ret = obj.invoke("StrCat", std::string("4"), std::string("2"));
	REQUIRE(ret.to <std::string>() == "42");

	ret = obj.invoke("StructTest", TestStruct1{"a", 1, 2});	//SIGSEGV on mono 3.2.3
	REQUIRE(ret.to<std::string>() == "a12");

	auto paramClass = image.classFromName("TestLib", "Param");
	auto param = paramClass.New();
    param.setField("a", 1);
    param.setField("b", 2);
    ret = obj.invoke("Sum", param);
    REQUIRE(ret.to<int>());

    MonoBind::ArrayWrapper<int> arr(MonoBind::Class::int32Class(), 10);
    for (int i = 0; i < arr.length(); ++i)
    {
        arr[i] = i;
    }

    ret = obj.invoke("SumArray", arr);
    REQUIRE(ret.to<int>() == 45);
    // TODO: delegate test
}

// TODO: exception test

TEST_CASE("Getter and Setter test", "[Object]")
{
    auto image = MonoBind::Domain::get().openAssembly("TestLib.dll").getImage();
	auto klass = image.classFromName("TestLib", "GetterSetterTest");
	REQUIRE(klass.raw() != nullptr);

	auto obj = klass.New();
	REQUIRE(obj.raw() != nullptr);

	obj.setField("_a", 40);
	auto a = obj.getField<int>("_a");
	REQUIRE(a == 40);

	obj.setField("_b", std::string("111"));
	auto b = obj.getField<std::string>("_b");
	REQUIRE(b == "111");

	obj.setProp("A", 40);
	REQUIRE(obj.getField<int>("_a") == 41);
	REQUIRE(obj.getProp<int>("A") == 42);

	obj.setProp("B", "222");
	REQUIRE(obj.getField<std::string>("_b") == "222");
	REQUIRE(obj.getProp<std::string>("B") == "222");

	auto fieldClass = image.classFromName("TestLib", "Field");
	auto fieldObj1 = fieldClass.New();
	fieldObj1.setField("a", 1);
	obj.setField("_field", fieldObj1);
	auto fieldObj1_ = obj.getField<MonoBind::Object>("_field");
	REQUIRE(fieldObj1_.getField<int>("a") == 1);

	auto fieldObj2 = fieldClass.New();
	fieldObj2.setField("a", 2);
	obj.setProp("F", fieldObj2);
	auto fieldObj2_ = obj.getProp<MonoBind::Object>("F");
	REQUIRE(fieldObj2_.getField<int>("a") == 2);

}

std::string g_str;
int g_i;

MonoBind::StringWrapper cfunc(MonoBind::StringWrapper str, int i) {
	g_str = str.toString();
	g_i = i;
	return "success";
}



TEST_CASE("C# call c func test", "[Interop]")
{
	MonoBind::regFunc("TestLib.InteropTest::CFunc(string,int)", (const void*)&cfunc);
	auto klass = MonoBind::Domain::get().openAssembly("TestLib.dll").getImage().classFromName("TestLib", "InteropTest");
	REQUIRE(klass.raw() != nullptr);

    auto ret = klass.invoke("RegFuncTest", "foo", 123); // XXX: not supported on 3.2.3
    REQUIRE(ret.to<std::string>() == "success");
    REQUIRE(g_str == "foo");
    REQUIRE(g_i == 123);
}


