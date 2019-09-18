#pragma once

namespace MonoBind
{
	class Class
	{
	public:
		inline Class(MonoClass* klass);

		inline MonoClass* raw() const;

        inline Object New();

        inline Method getMethod(const char* name);

		template<typename ...ArgsT>
		Object invoke(const char* name, ArgsT const& ... args);

		inline static Class& objectClass();
		inline static Class& byteClass();
		inline static Class& sbyteClass();
        inline static Class& int16Class();
        inline static Class& uint16Class();
        inline static Class& int32Class();
        inline static Class& uint32Class();
		inline static Class& voidClass();
        inline static Class& booleanClass();
        inline static Class& intptrClass();
        inline static Class& uintptrClass();
        inline static Class& int64Class();
        inline static Class& uint64Class();
        inline static Class& singleClass();
        inline static Class& doubleClass();
        inline static Class& charClass();
        inline static Class& stringClass();
        inline static Class& enumClass();
        inline static Class& arrayClass();
        inline static Class& threadClass();
        inline static Class& exceptionClass();
	private:
		MonoClass* m_class;
	};
}

