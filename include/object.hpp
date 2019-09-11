#pragma once

#include <mono/metadata/object.h>
#include <tchar.h>

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

		template<typename ...ArgsT>
		ObjectPtr invoke(const char* name, ArgsT& ... args);

		ObjectPtr invoke(const char* name);

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