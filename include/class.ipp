#pragma once


namespace MonoBind
{
	ObjectPtr Class::New()
	{
		return Object::createObject(Domain::get().raw(), m_class);
	}


}