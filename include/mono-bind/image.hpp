#pragma once

namespace MonoBind
{
	class Image
	{
	public:
		inline Image(MonoImage* image);

        inline Class classFromName(const char* nameSpace, const char* name);

		inline static Image& getCorlib();
	private:
		MonoImage* m_image;
	};
}