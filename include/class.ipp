#pragma once


namespace MonoBind
{
	ObjectPtr Class::New(DomainPtr domain)
	{
		return Object::createObject(domain->Raw(), m_class);
	}


}