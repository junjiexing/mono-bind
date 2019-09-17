#pragma once

#include <mono/metadata/metadata.h>
#include <mono/metadata/object.h>
#include <mono/metadata/appdomain.h>
#include <memory>
#include <string>

namespace MonoBind
{
	class Method
	{
	public:
		Method(MonoMethod* method)
			:m_method(method, [](MonoMethod* m) {mono_free_method(m); })
		{}


		template<typename ...ArgsT>
		ObjectPtr invoke(MonoObject* obj, ArgsT ... args);

		inline ObjectPtr invoke(MonoObject* obj, void** params = nullptr, MonoObject** exec = nullptr);

		MonoMethod* raw() const 
		{
			return m_method.get();
		}

		explicit operator bool() const noexcept
		{
			return raw() != nullptr;
		}


		static MonoString* convertArg(const char* str)
		{
			return mono_string_new(mono_domain_get(), str);
		}

		static MonoString* convertArg(const std::string& str)
		{
			return mono_string_new_len(mono_domain_get(), str.data(), str.size());
		}

		static MonoString* convertArg(std::string& str)
		{
			return mono_string_new_len(mono_domain_get(), str.data(), str.size());
		}

		static MonoString* convertArg(const wchar_t* str)
		{
			return mono_string_new_utf16(mono_domain_get(), reinterpret_cast<const mono_unichar2*>(str), wcslen(str));
		}

		static MonoString* convertArg(const std::wstring& str)
		{
			return mono_string_new_utf16(mono_domain_get(), reinterpret_cast<const mono_unichar2*>(str.data()), str.size());
		}

		template <typename T>
		static T* convertArg(std::reference_wrapper<T> arg)
		{
			return &arg.get();
		}

		template<typename T>
		static T* convertArg(T& arg)
		{
			return &arg;
		}

		template<typename T>
		static T* convertArg(T* arg)
		{
			return arg;
		}

	private:
		std::shared_ptr<MonoMethod> m_method;
	};
}