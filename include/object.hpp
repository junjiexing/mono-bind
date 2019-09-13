#pragma once

#include <mono/metadata/object.h>
#include <wchar.h>
#include <string>
#include <type_traits>

namespace MonoBind
{
	class Object;
	using ObjectPtr = std::shared_ptr<Object>;

	class Object
	{
	public:
		~Object()
		{
			mono_gchandle_free(m_gchandle);
		}

		static ObjectPtr createObject(MonoDomain* domain, MonoClass* klass)
		{
			auto object = mono_object_new(domain, klass);
			mono_runtime_object_init(object);

			return ObjectPtr(new Object(object));
		}

		static ObjectPtr attachObject(MonoObject* object)
		{
			return ObjectPtr(new Object(object));
		}

		MonoObject* raw() const;

		MonoClass* getClass() const;

		MonoDomain* getDomain() const;

// 		template<typename ...ArgsT>
// 		ObjectPtr invoke(const char* name, ArgsT& ... args);

		//TODO: ref & out

		template<typename ...ArgsT>
		ObjectPtr invoke(const char* name, ArgsT ... args);

		ObjectPtr invoke(const char* name);

		template<typename T>
		typename std::enable_if<!std::is_same<T, std::string>::value, T>::type to()
		{
			auto ret = reinterpret_cast<T*>(mono_object_unbox(m_object));
			return *ret;
		}

		template<typename T>
		typename std::enable_if<std::is_same<T, std::string>::value, T>::type to()
		{
			auto cStr = mono_string_to_utf8(reinterpret_cast<MonoString*>(m_object));
			std::string str(cStr);
			mono_free(cStr);
			return str;
		}

	private:
		MonoString* convertArg(const char* str)
		{
			return mono_string_new(getDomain(), str);
		}

		MonoString* convertArg(const std::string& str)
		{
			return mono_string_new_len(getDomain(), str.data(), str.size());
		}

		MonoString* convertArg(const wchar_t* str)
		{
			return mono_string_new_utf16(getDomain(), reinterpret_cast<const mono_unichar2*>(str), wcslen(str));
		}

		MonoString* convertArg(const std::wstring& str)
		{
			return mono_string_new_utf16(getDomain(), reinterpret_cast<const mono_unichar2*>(str.data()), str.size());
		}

		template<typename T>
		T* convertArg(T& arg)
		{
			return &arg;
		}

		template<typename T>
		T* convertArg(T* arg)
		{
			return arg;
		}

	private:
		Object(MonoObject* object)
			:m_object(object),
			m_gchandle(mono_gchandle_new(object, true))
		{

		}
		MonoObject* m_object;
		uint32_t m_gchandle;
	};
}