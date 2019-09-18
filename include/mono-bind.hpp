#pragma once

#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/loader.h>
#include <mono/metadata/object.h>
#include <mono/metadata/appdomain.h>
#include <mono/metadata/class.h>
#include <mono/metadata/metadata.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/jit/jit.h>

#include <cstring>
#include <cwchar>
#include <cassert>
#include <string>
#include <type_traits>
#include <memory>


namespace MonoBind
{
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

#include <mono-bind/array.hpp>
#include <mono-bind/method.hpp>
#include <mono-bind/type.hpp>
#include <mono-bind/object.hpp>
#include <mono-bind/class.hpp>
#include <mono-bind/image.hpp>
#include <mono-bind/assembly.hpp>
#include <mono-bind/domain.hpp>
#include <mono-bind/string.hpp>

#include <mono-bind/details/array.ipp>
#include <mono-bind/details/method.ipp>
#include <mono-bind/details/object.ipp>
#include <mono-bind/details/class.ipp>
#include <mono-bind/details/image.ipp>
#include <mono-bind/details/assembly.ipp>
#include <mono-bind/details/domain.ipp>
#include <mono-bind/details/type.ipp>
#include <mono-bind/details/string.ipp>
