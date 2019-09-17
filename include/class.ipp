#pragma once


#include "class.hpp"

namespace MonoBind
{
	ObjectPtr Class::New()
	{
		return Object::createObject(Domain::get().raw(), m_class);
	}

	Method Class::getMethod(const char* name)
	{
		MonoMethod* method = nullptr;
		void* iter = nullptr;
		while ((method = mono_class_get_methods(m_class, &iter)))
		{
			if (std::strcmp(mono_method_get_name(method), name) == 0) return Method(method);
		}

		return Method(nullptr);
	}

	template<typename ...ArgsT>
	ObjectPtr Class::invoke(const char* name, ArgsT const& ... args)
	{
		return getMethod(name).invoke(nullptr, args...);
	}

    Class& Class::intClass()
    {
	    static Class c(mono_get_int32_class());
        return c;
    }

}