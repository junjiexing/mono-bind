

#include <iostream>
#include <mono/jit/jit.h>
#include <mono/metadata/loader.h>
#include <mono/metadata/assembly.h>

MonoMethod* find_method(MonoClass* klass, const char* name)
{
	MonoMethod* method = nullptr;
	void* iter = nullptr;
	while ((method = mono_class_get_methods(klass, &iter)))
	{
		if (strcmp(mono_method_get_name(method), name) == 0) return method;
	}

	return nullptr;
}


int main()
{
	mono_set_assemblies_path(MONO_PATH_STR "\\lib\\mono\\4.5");

	auto domain = mono_jit_init("HelloHost.exe");

	auto assembly = mono_domain_assembly_open(domain, "Hello.dll");
	if (!assembly) return 1;

	auto image = mono_assembly_get_image(assembly);
	auto klass = mono_class_from_name(image, "Example", "Hello");
	if (!klass) return 1;

	auto instance = mono_object_new(domain, klass);
	mono_runtime_object_init(instance);

	auto method = find_method(klass, "SayHello");
	if (!method) return 1;

	mono_runtime_invoke(method, instance, nullptr, nullptr);

	mono_jit_cleanup(domain);

	return 0;
}

