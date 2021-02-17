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
		virtual void  SetMovementStartPosition(VECTOR2F* aPosition) = 0;
		const Enums::MovementPattern& GetPattern();
		const VECTOR2F& GetDirection() const;

	protected:
		VECTOR2F* myObjectsPosition;
		VECTOR2F myDirection;
		Enums::MovementPattern myPattern;
		float mySpeed;
		float myTotalTime;
	};
}


