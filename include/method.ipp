#pragma once

namespace MonoBind
{
	ObjectPtr Method::invoke(const ObjectPtr& obj, void** params, MonoObject** exec)
	{
		return invoke(obj->Raw());
	}

	ObjectPtr Method::invoke(MonoObject* obj, void** params, MonoObject** exec)
	{
		return Object::attachObject(mono_runtime_invoke(m_method, obj, params, exec));
	}

}