

#include <iostream>

#include <mono-bind.hpp>

int main()
{
	MonoBind::initPath(MONO_PATH_STR "/lib/mono/4.5");
	MonoBind::Domain::get().initJit("HelloHost.exe");
	auto klass = MonoBind::Domain::get().openAssembly("Hello.dll").getImage().classFromName("Example", "Hello");
	auto obj = klass.New();
	obj.invoke("SayHello", "libmono");

	return 0;
}