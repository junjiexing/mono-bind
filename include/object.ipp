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

 	ObjectPtr Object::invoke(const char* name)
 	{
 		Class klass = getClass();
 		Method method = klass.getMethod(name);
 		return method.invoke(m_object);
 	}

// 	template<typename ...ArgsT>
// 	ObjectPtr Object::invoke(const char* name, ArgsT& ... args)
// 	{
// 		void* monoArgs[] = { convertArg(args)... };
// 		Class klass = getClass();
// 		Method method = klass.getMethod(name);
// 		return method.invoke(m_object, monoArgs);
// 	}

	template<typename ...ArgsT>
	ObjectPtr Object::invoke(const char* name, ArgsT... args)
	{
		void* monoArgs[] = { convertArg(args)... };
		Class klass = getClass();
		Method method = klass.getMethod(name);
		return method.invoke(m_object, monoArgs);
	}

}