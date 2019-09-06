#pragma once

#include <mono/metadata/appdomain.h>


namespace MonoBind
{
	class Assembly
	{
	public:
		Assembly(MonoAssembly* assembly)
			:m_assembly(assembly)
		{}

		Image getImage();
	private:
		MonoAssembly* m_assembly;
	};


}

