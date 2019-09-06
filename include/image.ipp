#pragma once

namespace MonoBind
{

	Class Image::classFromName(const char* nameSpace, const char* name)
	{
		return Class(mono_class_from_name(m_image, nameSpace, name));
	}
}