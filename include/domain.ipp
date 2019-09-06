#pragma once

namespace MonoBind
{
	DomainPtr Domain::initJit(const char* file)
	{
		return std::shared_ptr<Domain>(new Domain(mono_jit_init(file)));
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