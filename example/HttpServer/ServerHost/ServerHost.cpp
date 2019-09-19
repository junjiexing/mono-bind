
#include <iostream>
#include <mono-bind.hpp>

int main()
{
	MonoBind::initDir(
		MONO_PATH_STR "/lib",
		MONO_PATH_STR "/etc",
		MONO_PATH_STR "/etc/mono/4.5/machine.config");
	MonoBind::Domain::get().initJit("ServerHost.exe", "v4.0.30319");
	MonoBind::Domain::get().setConfig(MONO_PATH_STR "/etc/mono/4.5", "machine.config");

	auto klass = MonoBind::Domain::get().openAssembly("ServerLib.dll").getImage().classFromName("ServerLib", "Server");
	auto obj = klass.New();
	obj.invoke("Start");
	std::cout << "press enter to exit" << std::endl;
	std::getchar();
	obj.invoke("Stop");
	return 0;
}
