#pragma once

#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-config.h>

#include <memory>

namespace MonoBind
{
	class Domain;
	using DomainPtr = std::shared_ptr<Domain>;
	using DomainWeakPtr = std::weak_ptr<Domain>;


	inline void initPath(const char* assembliesPath, const char* configFileName = nullptr)
	{
		mono_set_assemblies_path(assembliesPath);
		mono_config_parse(configFileName);
	}

	inline void initDir(const char* assemblyDir, const char* configDir, const char* configFileName = nullptr)
	{
		mono_set_dirs(assemblyDir, configDir);
		mono_config_parse(configFileName);
	}

}



#include <object.hpp>
#include <method.hpp>
#include <class.hpp>
#include <image.hpp>
#include <assembly.hpp>
#include <domain.hpp>

#include <object.ipp>
#include <method.ipp>
#include <class.ipp>
#include <image.ipp>
#include <assembly.ipp>
#include <domain.ipp>


