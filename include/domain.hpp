#pragma once

#include <mono/metadata/appdomain.h>
#include <mono/jit/jit.h>


namespace MonoBind
{
	class Domain
	{
	public:
        Domain(const Domain&) = delete;
        Domain& operator=(const Domain&) = delete;
        Domain(Domain&&) = delete;
        Domain& operator=(Domain&&) = delete;

        inline static Domain& get();

        inline void initJit(const char* file);
        inline void initJit(const char* file, const char* ver);

        inline Assembly openAssembly(const char* name);

        inline MonoDomain* raw();

        inline void cleanup();

		~Domain()
		{
			cleanup();
		}
	private:
		Domain() = default;


		MonoDomain* m_domain = nullptr;
	};
}

