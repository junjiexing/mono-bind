#pragma once

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

		inline void setConfig(const char* base_dir, const char* config_file_name);

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

