#pragma once

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