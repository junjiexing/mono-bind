#pragma once

namespace MonoBind
{
    Object::Object(MonoObject *object)
            :m_object(object),
             m_gchandle(mono_gchandle_new(object, true))
    {}

    Object::Object(const Object &object)
        :m_object(object.m_object),
        m_gchandle(mono_gchandle_new(object.m_object, true))
    {}

    Object::Object(Object &&other) noexcept
        :m_object(other.m_object),
        m_gchandle(other.m_gchandle)
    {
        other.m_object = nullptr;
        other.m_gchandle = 0;
    }

    Object &Object::operator=(const Object &other)
    {
        if (m_gchandle != 0)  mono_gchandle_free(m_gchandle);

        m_object = other.m_object;
        m_gchandle = mono_gchandle_new(m_object, true);

        return *this;
    }

    Object &Object::operator=(Object &&other) noexcept
    {
        if (m_gchandle != 0)  mono_gchandle_free(m_gchandle);

        m_object = other.m_object;
        other.m_object = nullptr;
        m_gchandle = other.m_gchandle;
        other.m_gchandle = 0;

        return *this;
    }

    Object::~Object()
    {
        if (m_gchandle != 0)  mono_gchandle_free(m_gchandle);
    }

    MonoObject* Object::raw() const
	{
		return m_object;
	}

	MonoClass* Object::getClass() const
	{
		return mono_object_get_class(m_object);
	}

	MonoDomain* Object::getDomain() const
	{
		return mono_object_get_domain(m_object);
	}

	template<typename ...ArgsT>
	Object Object::invoke(const char* name, ArgsT const&... args)
	{
		Class klass(getClass());
		auto method = klass.getMethod(name);
		return method.invoke(m_object, args...);
	}

	template<typename T>
	typename std::enable_if<!std::is_same<T, std::string>::value, T>::type Object::to()
	{
		auto ret = reinterpret_cast<T*>(mono_object_unbox(m_object));
		return *ret;
	}

	template<typename T>
	typename std::enable_if<std::is_same<T, std::string>::value, T>::type Object::to()
	{
		auto cStr = mono_string_to_utf8(reinterpret_cast<MonoString*>(m_object));
		std::string str(cStr);
		mono_free(cStr);
		return str;
	}

	template<typename T>
	typename std::enable_if<
	        !std::is_same<T, std::string>::value
	        && !std::is_same<T, Object>::value,
	        T>::type  Object::getField(const char* name)
	{
		auto field = mono_class_get_field_from_name(getClass(), name);
		T v;
		mono_field_get_value(m_object, field, &v);
		return v;
	}

	template<typename T>
	typename std::enable_if<std::is_same<T, std::string>::value, T>::type Object::getField(const char* name)
	{
		auto field = mono_class_get_field_from_name(getClass(), name);
		StringWrapper str;
		mono_field_get_value(m_object, field, &str);
		return str.toString();
	}

    template<typename T>
    typename std::enable_if<std::is_same<T, Object>::value, T>::type Object::getField(const char* name)
    {
        auto field = mono_class_get_field_from_name(getClass(), name);
        MonoObject* mobj;
        mono_field_get_value(m_object, field, &mobj);
        return Object(mobj);
    }

	template<typename T>
	void Object::setField(const char* name, T v)
	{
		auto field = mono_class_get_field_from_name(getClass(), name);
		mono_field_set_value(m_object, field, Method::convertArg(v));
	}

	template<typename T>
    typename std::enable_if<!std::is_same<T, Object>::value, T>::type Object::getProp(const char* name)
	{
		auto prop = mono_class_get_property_from_name(getClass(), name);
		//TODO: exception
		return Object(mono_property_get_value(prop, m_object, nullptr, nullptr)).to<T>();
	}

    template<typename T>
    typename std::enable_if<std::is_same<T, Object>::value, T>::type Object::getProp(const char* name)
    {
        auto prop = mono_class_get_property_from_name(getClass(), name);
        //TODO: exception
        return Object(mono_property_get_value(prop, m_object, nullptr, nullptr));
    }


    template<typename T>
	void Object::setProp(const char* name, T v)
	{
		auto prop = mono_class_get_property_from_name(getClass(), name);
		void* params[] = { Method::convertArg(v) };
		mono_property_set_value(prop, m_object, params, nullptr);
		//TODO: exception
	}



}