#pragma once

namespace MonoBind
{
	inline Image Assembly::getImage()
	{
		return Image(mono_assembly_get_image(m_assembly));
	}
}