#pragma once

#include <mono/metadata/metadata.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/class.h>
#include <string>


namespace MonoBind
{
	class Type
	{
	public:
		Type(MonoType* type)
			:m_type(type)
		{}

		MonoType* raw()
		{
			return m_type;
		}

		std::string fullName()
		{
			return mono_type_full_name(m_type);
		}

		std::string name()
		{
			return mono_type_get_name(m_type);
		}

		MonoTypeEnum getType()
		{
			return static_cast<MonoTypeEnum>(mono_type_get_type(m_type));
		}

		bool operator==(std::string name)
		{
			return name == this->name();
		}

		bool operator==(MonoTypeEnum type)
		{
			return type == getType();
		}
		// TODO: other functions
	private:
		MonoType* m_type;
	};
}
