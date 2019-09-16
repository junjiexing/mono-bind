#pragma once

namespace MonoBind
{

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

	ObjectPtr Object::invoke(const char* name, void** params, MonoObject** exec)
	{
		Class klass(getClass());
		auto method = klass.getMethod(name);
		auto obj = Object::attachObject(mono_runtime_invoke(method, m_object, params, exec));
		mono_free_method(method);
		return obj;
	}

	template<typename ...ArgsT>
	ObjectPtr Object::invoke(const char* name, ArgsT... args)
	{
		void* monoArgs[] = { convertArg(args)... };
		return invoke(name, monoArgs);
	}

}