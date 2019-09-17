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
		~Object();

		static ObjectPtr createObject(MonoDomain* domain, MonoClass* klass);

		static ObjectPtr attachObject(MonoObject* object);

		MonoObject* raw() const;

		MonoClass* getClass() const;

		MonoDomain* getDomain() const;

		template<typename ...ArgsT>
		ObjectPtr invoke(const char* name, ArgsT const& ... args);

		// TODO: invoke support object

		template<typename T>
		typename std::enable_if<!std::is_same<T, std::string>::value, T>::type to();

		template<typename T>
		typename std::enable_if<std::is_same<T, std::string>::value, T>::type to();

		template<typename T>
		typename std::enable_if<!std::is_same<T, std::string>::value, T>::type getField(const char* name);

		template<typename T>
		typename std::enable_if<std::is_same<T, std::string>::value, T>::type getField(const char* name);

		template<typename T>
		typename std::enable_if<!std::is_same<T, std::string>::value, void>::type setField(const char* name, T v);

		template<typename T>
		typename std::enable_if<std::is_same<T, std::string>::value, void>::type setField(const char* name, T v);

		// TODO: getField and setField support object


		template<typename T>
		T getProp(const char* name);

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