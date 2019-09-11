#include <mono-bind.hpp>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

struct TestIniter
{
	TestIniter()
	{
		MonoBind::init(MONO_PATH_STR "\\lib\\mono\\4.5");
	}
} test_init_instance;



TEST_CASE("No param member function invoke test", "[invoke]")
{
	auto domain = MonoBind::Domain::initJit("Test.exe");
	REQUIRE(domain->Raw() != nullptr);
	auto klass = domain->openAssembly("TestLib.dll").getImage().classFromName("TestLib", "InvokeTest1");
	REQUIRE(klass.Raw() != nullptr);
	auto obj = klass.New(domain);
	REQUIRE(obj->Raw() != nullptr);
	auto ret = obj->invoke("Return42");
	REQUIRE(ret->to<int>() == 42);
}

