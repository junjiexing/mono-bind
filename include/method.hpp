#pragma once

#include <mono/metadata/metadata.h>

namespace MonoBind
{
	class Method
	{
	public:
		Method(MonoMethod* method)
			:m_method(method)
		{}

		ObjectPtr invoke(const ObjectPtr& obj, void** params = nullptr, MonoObject** exec = nullptr);
		ObjectPtr invoke(MonoObject* obj, void** params = nullptr, MonoObject** exec = nullptr);
	private:
		MonoMethod* m_method;
	};


}