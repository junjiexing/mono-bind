#pragma once

#include <mono/metadata/appdomain.h>
#include <mono/jit/jit.h>


namespace MonoBind
{
	class Domain
	{
	public:
		static Domain& get();

		void initJit(const char* file);
		void initJit(const char* file, const char* ver);

		Assembly openAssembly(const char* name);

		MonoDomain* raw();

		void cleanup()
		{
			if (m_domain)
			{
				mono_jit_cleanup(m_domain);
				m_domain = nullptr;
			}

		}

		~Domain()
		{
			cleanup();
		}
	private:
		Domain() = default;
		Domain(const Domain&) = delete;
 		Domain& operator=(const Domain&) = delete;
 		Domain(Domain&&) = delete;
 		Domain& operator=(Domain&&) = delete;


		MonoDomain* m_domain = nullptr;
	};
}

