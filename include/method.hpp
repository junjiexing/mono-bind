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

		inline MonoMethod* raw() const;

		inline explicit operator bool() const noexcept;


        inline static MonoString* convertArg(const char* str);

        inline static MonoString* convertArg(const std::string& str);

        inline static MonoString* convertArg(std::string& str);

        inline static MonoString* convertArg(const wchar_t* str);

        inline static MonoString* convertArg(const std::wstring& str);

        inline static MonoObject* convertArg(ObjectPtr obj);

        template <typename T>
        static T* convertArg(std::reference_wrapper<T> arg);

		template<typename T>
		static T* convertArg(T& arg);

		template<typename T>
		static T* convertArg(T* arg);

	private:
		std::shared_ptr<MonoMethod> m_method;
	};
}