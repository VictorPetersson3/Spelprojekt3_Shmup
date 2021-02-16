#pragma once
#include "GameObject.h"
namespace Studio
{
	class MousePointer : public GameObject
	{
	public:
		MousePointer();
		~MousePointer();
		void Update(VECTOR2F aPosition);
	};

}

