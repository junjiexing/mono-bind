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

        inline Class classFromName(const char* nameSpace, const char* name);

		inline static Image& getCorlib();
	private:
		MonoImage* m_image;
	};
}