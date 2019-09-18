#pragma once

namespace MonoBind
{
    Class::Class(MonoClass *klass)
        :m_class(klass)
    {}

    MonoClass *Class::raw() const { return m_class; }

    Object Class::New()
	{
        auto object = mono_object_new(mono_domain_get(), m_class);
        mono_runtime_object_init(object);
		return Object(object);
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

	// invoke static member function
	template<typename ...ArgsT>
	Object Class::invoke(const char* name, ArgsT const& ... args)
	{
		return getMethod(name).invoke(nullptr, args...);
	}

    Class& Class::int32Class()
    {
	    static Class c(mono_get_int32_class());
        return c;
    }

    Class &Class::objectClass()
    {
	    static Class c(mono_get_object_class());
        return c;
    }

    Class &Class::byteClass()
    {
	    static Class c(mono_get_byte_class());
        return c;
    }

    Class &Class::voidClass()
    {
	    static Class c(mono_get_void_class());
        return c;
    }

    Class &Class::booleanClass()
    {
	    static Class c(mono_get_boolean_class());
        return c;
    }

    Class &Class::sbyteClass()
    {
	    static Class c(mono_get_sbyte_class());
        return c;
    }

    Class &Class::int16Class()
    {
        static Class c(mono_get_int16_class());
        return c;
    }

    Class &Class::uint16Class()
    {
        static Class c(mono_get_uint16_class());
        return c;
    }

    Class& Class::uint32Class()
    {
        static Class c(mono_get_uint32_class());
        return c;
    }

    Class& Class::intptrClass()
    {
        static Class c(mono_get_intptr_class());
        return c;
    }

    Class& Class::uintptrClass()
    {
        static Class c(mono_get_uintptr_class());
        return c;
    }

    Class& Class::int64Class()
    {
        static Class c(mono_get_int64_class());
        return c;
    }

    Class& Class::uint64Class()
    {
        static Class c(mono_get_uint64_class());
        return c;
    }

    Class& Class::singleClass()
    {
        static Class c(mono_get_single_class());
        return c;
    }

    Class& Class::doubleClass()
    {
        static Class c(mono_get_double_class());
        return c;
    }

    Class& Class::charClass()
    {
        static Class c(mono_get_char_class());
        return c;
    }

    Class& Class::stringClass()
    {
        static Class c(mono_get_string_class());
        return c;
    }

    Class& Class::enumClass()
    {
        static Class c(mono_get_enum_class());
        return c;
    }

    Class& Class::arrayClass()
    {
        static Class c(mono_get_array_class());
        return c;
    }

    Class& Class::threadClass()
    {
        static Class c(mono_get_thread_class());
        return c;
    }

    Class& Class::exceptionClass()
    {
        static Class c(mono_get_exception_class());
        return c;
    }
}