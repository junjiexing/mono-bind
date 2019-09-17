#pragma once

#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/loader.h>

#include <memory>

namespace MonoBind
{
	class Object;
	using ObjectPtr = std::shared_ptr<Object>;


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

	inline void regFunc(const char* name, const void* method)
	{
		mono_add_internal_call(name, method);
	}
}

#include <array.hpp>
#include <method.hpp>
#include <type.hpp>
#include <object.hpp>
#include <class.hpp>
#include <image.hpp>
#include <assembly.hpp>
#include <domain.hpp>
#include <string_wrapper.hpp>

#include <array.ipp>
#include <method.ipp>
#include <object.ipp>
#include <class.ipp>
#include <image.ipp>
#include <assembly.ipp>
#include <domain.ipp>
#include <type.ipp>

