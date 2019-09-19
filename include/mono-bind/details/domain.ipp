#pragma once

#ifdef MONO_DOMAIN_SET_CONFIG_PATCH		//only for mono 3.2.8 and lower version 

#include <windows.h>

typedef struct {
	MonoObject object;
	MonoString* application_base;
	MonoString* application_name;
	MonoString* cache_path;
	MonoString* configuration_file;
	MonoString* dynamic_base;
	MonoString* license_file;
	MonoString* private_bin_path;
	MonoString* private_bin_path_probe;
	MonoString* shadow_copy_directories;
	MonoString* shadow_copy_files;
	MonoBoolean publisher_policy;
	MonoBoolean path_changed;
	int loader_optimization;
	MonoBoolean disallow_binding_redirects;
	MonoBoolean disallow_code_downloads;
	MonoObject* activation_arguments;
	MonoObject* domain_initializer;
	MonoObject* application_trust;
	MonoArray* domain_initializer_args;
	MonoBoolean disallow_appbase_probe;
	MonoArray* configuration_bytes;
	MonoArray* serialized_non_primitives;
} MonoAppDomainSetup;


struct _MonoDomain {
	CRITICAL_SECTION    lock;
	void* mp;
	void* code_mp;
	MonoAppDomainSetup* setup;
};


static void mono_domain_set_config(MonoDomain* domain, const char* base_dir, const char* config_file_name)
{
	MONO_OBJECT_SETREF(domain->setup, application_base, mono_string_new(domain, base_dir));
	MONO_OBJECT_SETREF(domain->setup, configuration_file, mono_string_new(domain, config_file_name));
}

#endif


namespace MonoBind
{

	MonoBind::Domain& Domain::get()
	{
		static Domain domain;
		return domain;
	}

	void Domain::initJit(const char* file)
	{
		assert(m_domain == nullptr);
		m_domain = mono_jit_init(file);
	}

	void Domain::initJit(const char* file, const char* ver)
	{
		assert(m_domain == nullptr);
		m_domain = mono_jit_init_version(file, ver);
	}


	void Domain::setConfig(const char* base_dir, const char* config_file_name)
	{
		mono_domain_set_config(m_domain, base_dir, config_file_name);
	}

	MonoDomain* Domain::raw()
	{
		return m_domain;
	}

    void Domain::cleanup()
    {
        if (m_domain)
        {
            mono_jit_cleanup(m_domain);
            m_domain = nullptr;
        }
    }

	Assembly Domain::openAssembly(const char* name)
	{
		return Assembly(mono_domain_assembly_open(m_domain, name));
	}

}