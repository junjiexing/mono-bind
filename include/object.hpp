#pragma once

#include <mono/metadata/object.h>

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