#pragma once

#include <mono/metadata/appdomain.h>
#include <mono/jit/jit.h>


namespace MonoBind
{
	class Domain
	{
	public:
		static DomainPtr initJit(const char* file);

		Assembly openAssembly(const char* name);

		MonoDomain* Raw();

		~Domain()
		{
			mono_jit_cleanup(m_domain);
		}
	private:
		Domain() = delete;
		Domain(MonoDomain* domain) : m_domain(domain) {}
		Domain(const Domain&) = delete;
 		Domain& operator=(const Domain&) = delete;
 		//TODO: Ö§³Ömove ctor£¿ 
 		Domain(Domain&&) = delete;
 		Domain& operator=(Domain&&) = delete;


		MonoDomain* m_domain = nullptr;
	};
}

