#pragma once
#include <cassert>

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

	inline MonoDomain* Domain::raw()
	{
		return m_domain;
	}


	inline Assembly Domain::openAssembly(const char* name)
	{
		return Assembly(mono_domain_assembly_open(m_domain, name));
	}

}