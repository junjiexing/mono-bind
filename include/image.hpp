#pragma once

#include <mono/metadata/appdomain.h>
#include <mono/metadata/class.h>

namespace MonoBind
{
	class Image
	{
	public:
		explicit Image(MonoImage* image)
			:m_image(image)
		{}

		Class classFromName(const char* nameSpace, const char* name);
	private:
		MonoImage* m_image;
	};
}