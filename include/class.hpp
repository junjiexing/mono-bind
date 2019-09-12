#pragma once

#include <mono/metadata/class.h>



namespace MonoBind
{
	class Class
	{
	public:
		Class(MonoClass* klass)
			:m_class(klass)
		{}

		MonoClass* raw() { return m_class; };

		ObjectPtr New();

		Method getMethod(const char* name)
		{
			MonoMethod* method = nullptr;
			void* iter = nullptr;
			while ((method = mono_class_get_methods(m_class, &iter)))
			{
				if (strcmp(mono_method_get_name(method), name) == 0) return Method(method);
			}

			return Method(nullptr);
		}
	private:
		MonoClass* m_class;
	};
}

