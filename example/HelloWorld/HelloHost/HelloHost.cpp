

#include <iostream>

#include <mono-bind.hpp>

int main()
{
	MonoBind::init(MONO_PATH_STR "\\lib\\mono\\4.5");
	auto domain = MonoBind::Domain::initJit("HelloHost.exe");
	auto klass = domain->openAssembly("Hello.dll").getImage().classFromName("Example", "Hello");
	auto method = klass.getMethod("SayHello");
	auto obj = klass.New(domain);
	method.invoke(obj);

	return 0;
}