#pragma once

namespace MonoBind
{
	Object::~Object()
	{
		std::cout << "free" << m_gchandle << std::endl;
		mono_gchandle_free(m_gchandle);
	}

	ObjectPtr Object::createObject(MonoDomain* domain, MonoClass* klass)
	{
		auto object = mono_object_new(domain, klass);
		mono_runtime_object_init(object);
		// TODO: invoke ctor

		return ObjectPtr(new Object(object));
	}

	ObjectPtr Object::attachObject(MonoObject* object)
	{
		return ObjectPtr(new Object(object));
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
	ObjectPtr Object::invoke(const char* name, ArgsT const&... args)
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
	typename std::enable_if<!std::is_same<T, std::string>::value, T>::type Object::getField(const char* name)
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
		MonoString* mstr;
		mono_field_get_value(m_object, field, &mstr);
		auto cStr = mono_string_to_utf8(mstr);
		std::string str(cStr);
		mono_free(cStr);
		return str;
	}

	template<typename T>
	typename std::enable_if<!std::is_same<T, std::string>::value, void>::type Object::setField(const char* name, T v)
	{
		auto field = mono_class_get_field_from_name(getClass(), name);
		mono_field_set_value(m_object, field, &v);
	}

	template<typename T>
	typename std::enable_if<std::is_same<T, std::string>::value, void>::type Object::setField(const char* name, T v)
	{
		auto field = mono_class_get_field_from_name(getClass(), name);
		mono_field_set_value(m_object, field, Method::convertArg(v));
	}

	template<typename T>
	T Object::getProp(const char* name)
	{
		auto prop = mono_class_get_property_from_name(getClass(), name);
		auto obj = Object::attachObject(mono_property_get_value(prop, m_object, nullptr, nullptr));
		//TODO: exception
		return obj->to<T>();
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