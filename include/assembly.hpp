#pragma once

namespace MonoBind
{
	class Assembly
	{
	public:
		inline Assembly(MonoAssembly* assembly);

		inline Image getImage();
	private:
		MonoAssembly* m_assembly;
	};


}

