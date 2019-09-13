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


TEST_CASE("Invoke member function without param test", "[invoke]")
{
	MonoBind::Domain::get().initJit("Test1", "v4.0.30319");
	REQUIRE(MonoBind::Domain::get().raw() != nullptr);
	auto klass = MonoBind::Domain::get().openAssembly("TestLib.dll").getImage().classFromName("TestLib", "InvokeTest1");
	REQUIRE(klass.raw() != nullptr);
	auto obj = klass.New();
	REQUIRE(obj->raw() != nullptr);

	auto ret = obj->invoke("ReturnShort");
	REQUIRE(ret->to<short>() == 42);

	ret = obj->invoke("ReturnInt");
	REQUIRE(ret->to<int>() == 42);

	ret = obj->invoke("ReturnInt32");
	REQUIRE(ret->to<int>() == 42);


	ret = obj->invoke("ReturnString");
	REQUIRE(ret->to<std::string>() == "42");
}

TEST_CASE("Invoke member function with params test", "[invoke]")
{
	auto klass = MonoBind::Domain::get().openAssembly("TestLib.dll").getImage().classFromName("TestLib", "InvokeTest2");
	REQUIRE(klass.raw() != nullptr);
	{
		auto obj = klass.New();
		REQUIRE(obj->raw() != nullptr);

		auto ret = obj->invoke("CubicSum", -80538738812075974, 80435758145817515, 12602123297335631);
		REQUIRE(ret->to<int>() == 42);
	}

	MonoBind::Domain::get().cleanup();	// FIXME: ???
}


