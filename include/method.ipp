#pragma once


#include "method.hpp"

namespace MonoBind
{
	Object Method::invoke(MonoObject* obj, void** params, MonoObject** exec)
	{
		return Object(mono_runtime_invoke(m_method.get(), obj, params, exec));;
	}

	template<typename ...ArgsT>
	Object Method::invoke(MonoObject* obj, ArgsT... args)
	{
		void* monoArgs[] = { convertArg(args)... };
		return invoke(obj, monoArgs);
	}

    MonoMethod *Method::raw() const
    {
        return m_method.get();
    }

    Method::operator bool() const noexcept
    {
        return raw() != nullptr;
    }

    MonoString *Method::convertArg(const char *str)
    {
        return mono_string_new(mono_domain_get(), str);
    }

    MonoString *Method::convertArg(const std::string &str)
    {
        return mono_string_new_len(mono_domain_get(), str.data(), str.size());
    }

    MonoString *Method::convertArg(std::string &str)
    {
        return mono_string_new_len(mono_domain_get(), str.data(), str.size());
    }

    MonoString *Method::convertArg(const wchar_t *str)
    {
        return mono_string_new_utf16(mono_domain_get(), reinterpret_cast<const mono_unichar2*>(str), wcslen(str));
    }

    MonoString *Method::convertArg(const std::wstring &str)
    {
        return mono_string_new_utf16(mono_domain_get(), reinterpret_cast<const mono_unichar2*>(str.data()), str.size());
    }

    MonoObject *Method::convertArg(Object obj)
    {
        return obj.raw();
    }

    template<typename T>
    T *Method::convertArg(std::reference_wrapper<T> arg)
    {
        return &arg.get();
    }

    template<typename T>
    T *Method::convertArg(T &arg)
    {
        return &arg;
    }

    template<typename T>
    T *Method::convertArg(T *arg)
    {
        return arg;
    }

    template<typename T>
    MonoArray *Method::convertArg(Array<T>& arg)
    {
        return arg.raw();
    }
}