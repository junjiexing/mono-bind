#pragma once

#include "image.hpp"

namespace MonoBind
{

	Class Image::classFromName(const char* nameSpace, const char* name)
	{
		return Class(mono_class_from_name(m_image, nameSpace, name));
	}

    Image &Image::getCorlib()
    {
	    static Image img(mono_get_corlib());
        return img;
    }
}