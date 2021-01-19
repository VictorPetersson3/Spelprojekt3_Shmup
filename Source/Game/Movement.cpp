#include "stdafx.h"
#include "Movement.h"

namespace Studio
{
	Movement::~Movement()
	{
		// TODO: ???
	}

	const Enums::MovementPattern& Movement::GetPattern()
	{
		return myPattern;
	}
}

