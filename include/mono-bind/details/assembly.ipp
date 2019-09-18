#pragma once

namespace MonoBind
{
    Assembly::Assembly(MonoAssembly *assembly)
        :m_assembly(assembly)
    {}

    inline Image Assembly::getImage()
	{
		return Image(mono_assembly_get_image(m_assembly));
	}
}