#pragma once

namespace MonoBind
{
	class Type
	{
	public:
		inline Type(MonoType* type);

        inline MonoType* raw();

        inline std::string fullName();
        inline std::string name();
        inline MonoTypeEnum getType();

        inline bool operator==(const std::string& name);
        inline bool operator==(MonoTypeEnum type);
		// TODO: other functions
	private:
		MonoType* m_type;
	};

}
