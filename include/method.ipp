#pragma once

namespace MonoBind
{
	ObjectPtr Method::invoke(const ObjectPtr& obj)
	{
		return Object::attachObject(mono_runtime_invoke(m_method, obj->raw(), nullptr, nullptr));
	}
}