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

		ObjectPtr invoke(const ObjectPtr& obj);
	private:
		MonoMethod* m_method;
	};


}