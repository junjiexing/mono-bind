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
			// TODO: invoke ctor

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
		ObjectPtr invoke(const char* name, ArgsT ... args);

		ObjectPtr invoke(const char* name, void** params = nullptr, MonoObject** exec = nullptr);

		// TODO: invoke support object

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

		template<typename T>
		typename std::enable_if<!std::is_same<T, std::string>::value, T>::type getField(const char* name)
		{
			auto field = mono_class_get_field_from_name(getClass(), name);
			T v;
			mono_field_get_value(m_object, field, &v);
			return v;
		}

		template<typename T>
		typename std::enable_if<std::is_same<T, std::string>::value, T>::type getField(const char* name)
		{
			auto field = mono_class_get_field_from_name(getClass(), name);
			MonoString* mstr;
			mono_field_get_value(m_object, field, &mstr);
			auto cStr = mono_string_to_utf8(mstr);
			std::string str(cStr);
			mono_free(cStr);
			return str;
		}

		template<typename T>
		typename std::enable_if<!std::is_same<T, std::string>::value, void>::type setField(const char* name, T v)
		{
			auto field = mono_class_get_field_from_name(getClass(), name);
			mono_field_set_value(m_object, field, &v);
		}

		template<typename T>
		typename std::enable_if<std::is_same<T, std::string>::value, void>::type setField(const char* name, T v)
		{
			auto field = mono_class_get_field_from_name(getClass(), name);
			mono_field_set_value(m_object, field, convertArg(std::forward<T>(v)));
		}

		// TODO: getField and setField support object


		template<typename T>
		T getProp(const char* name)
		{
			auto prop = mono_class_get_property_from_name(getClass(), name);
			auto obj = Object::attachObject(mono_property_get_value(prop, m_object, nullptr, nullptr));
			//TODO: exception
			return obj->to<T>();
		}

		template<typename T>
		void setProp(const char* name, T v)
		{
			auto prop = mono_class_get_property_from_name(getClass(), name);
			void* params[] = { convertArg(v) };
			mono_property_set_value(prop, m_object, params, nullptr);
			//TODO: exception
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

		template <typename T>
		T* convertArg(std::reference_wrapper<T> arg)
        {
		    return &arg.get();
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