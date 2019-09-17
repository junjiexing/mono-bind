#pragma once


namespace MonoBind
{
	ObjectPtr Method::invoke(MonoObject* obj, void** params, MonoObject** exec)
	{
		return Object::attachObject(mono_runtime_invoke(m_method.get(), obj, params, exec));;
	}

	template<typename ...ArgsT>
	ObjectPtr Method::invoke(MonoObject* obj, ArgsT... args)
	{
		void* monoArgs[] = { convertArg(args)... };
		return invoke(obj, monoArgs);
	}

}