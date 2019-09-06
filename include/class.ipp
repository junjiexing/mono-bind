#pragma once


namespace MonoBind
{
	ObjectPtr Class::New(DomainPtr domain)
	{
		return Object::createObject(domain->raw(), m_class);
	}


}