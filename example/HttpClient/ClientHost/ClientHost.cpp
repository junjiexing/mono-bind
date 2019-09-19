
#include <iostream>
#include <string>
#include <mono-bind.hpp>

int main()
{
	MonoBind::initDir(
		MONO_PATH_STR "/lib",
		MONO_PATH_STR "/etc",
		MONO_PATH_STR "/etc/mono/4.5/machine.config");
	MonoBind::Domain::get().initJit("ServerHost.exe", "v4.0.30319");
	MonoBind::Domain::get().setConfig(MONO_PATH_STR "/etc/mono/4.5", "machine.config");

	auto klass = MonoBind::Domain::get().openAssembly("ClientLib.dll").getImage().classFromName("ClientLib", "Client");
	auto obj = klass.New();
	auto content = obj.invoke("Get", "http://www.cplusplus.com/").to<std::string>();
	// content is utf-8 encoding
	std::cout << content << std::endl;
	return 0;
}
