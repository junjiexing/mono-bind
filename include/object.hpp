#pragma once

#include <mono/metadata/object.h>
#include <wchar.h>
#include <string>
#include <type_traits>

namespace MonoBind
{
	class Object
	{
	public:
		~Object()
        {
            mono_gchandle_free(m_gchandle);
        }

		inline static ObjectPtr createObject(MonoDomain* domain, MonoClass* klass);

		inline static ObjectPtr attachObject(MonoObject* object);

		inline MonoObject* raw() const;

        inline MonoClass* getClass() const;

        inline MonoDomain* getDomain() const;

		template<typename ...ArgsT>
		ObjectPtr invoke(const char* name, ArgsT const& ... args);

		template<typename T>
		typename std::enable_if<!std::is_same<T, std::string>::value, T>::type to();

		template<typename T>
		typename std::enable_if<std::is_same<T, std::string>::value, T>::type to();

		// TODO: toArray()

		template<typename T>
		typename std::enable_if<
		        !std::is_same<T, std::string>::value
		        && !std::is_same<T, ObjectPtr>::value,
		        T>::type getField(const char* name);

        template<typename T>
        typename std::enable_if<std::is_same<T, std::string>::value, T>::type getField(const char* name);

        template<typename T>
        typename std::enable_if<std::is_same<T, ObjectPtr>::value, T>::type getField(const char* name);

		template<typename T>
		void setField(const char* name, T v);



        template<typename T>
        typename std::enable_if<!std::is_same<T, ObjectPtr>::value, T>::type getProp(const char* name);

        template<typename T>
        typename std::enable_if<std::is_same<T, ObjectPtr>::value, T>::type getProp(const char* name);

		template<typename T>
		void setProp(const char* name, T v);

	private:
		Object(MonoObject* object)
			:m_object(object),
			m_gchandle(mono_gchandle_new(object, true))
		{}
		MonoObject* m_object;
		uint32_t m_gchandle;
	};
}