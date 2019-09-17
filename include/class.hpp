#pragma once

#include <mono/metadata/class.h>
#include <cstring>


namespace MonoBind
{
	class Class
	{
	public:
		explicit Class(MonoClass* klass)
			:m_class(klass)
		{}

		MonoClass* raw() { return m_class; };

        inline ObjectPtr New();

        inline Method getMethod(const char* name);

		template<typename ...ArgsT>
		ObjectPtr invoke(const char* name, ArgsT const& ... args);

	private:
		MonoClass* m_class;
	};
}

