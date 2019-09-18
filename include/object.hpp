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
        inline explicit Object(MonoObject* object);
        inline Object(const Object& object);
        inline Object(Object&& other) noexcept;
        inline Object& operator=(const Object& other);
        inline Object& operator=(Object&& other) noexcept;

        inline ~Object();

		inline MonoObject* raw() const;

        inline MonoClass* getClass() const;

        inline MonoDomain* getDomain() const;

		template<typename ...ArgsT>
		Object invoke(const char* name, ArgsT const& ... args);

		template<typename T>
		typename std::enable_if<!std::is_same<T, std::string>::value, T>::type to();

		template<typename T>
		typename std::enable_if<std::is_same<T, std::string>::value, T>::type to();

		// TODO: toArray()

		template<typename T>
		typename std::enable_if<
		        !std::is_same<T, std::string>::value
		        && !std::is_same<T, Object>::value,
		        T>::type getField(const char* name);

        template<typename T>
        typename std::enable_if<std::is_same<T, std::string>::value, T>::type getField(const char* name);

        template<typename T>
        typename std::enable_if<std::is_same<T, Object>::value, T>::type getField(const char* name);

		template<typename T>
		void setField(const char* name, T v);



        template<typename T>
        typename std::enable_if<!std::is_same<T, Object>::value, T>::type getProp(const char* name);

        template<typename T>
        typename std::enable_if<std::is_same<T, Object>::value, T>::type getProp(const char* name);

		template<typename T>
		void setProp(const char* name, T v);

	private:
		MonoObject* m_object{};
		uint32_t m_gchandle{};
	};
}