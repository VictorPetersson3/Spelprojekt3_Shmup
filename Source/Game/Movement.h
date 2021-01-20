#pragma once
#include "Enums.h"
namespace Studio
{
	class Movement
	{
	public:
		Movement() = default;
		virtual ~Movement();
		virtual void Update() = 0; // pure virtual
		const Enums::MovementPattern& GetPattern();

	protected:
		VECTOR2F* myObjectsPosition;
		Enums::MovementPattern myPattern;
		float mySpeed;
		float myTotalTime;
	};
}


