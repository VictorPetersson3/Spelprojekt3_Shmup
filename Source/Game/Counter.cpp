#include "stdafx.h"
#include "Counter.h"
#include "Timer.h"
namespace Studio
{
	void Counter::SetInterval(const float anInterval)
	{
		myInterval = anInterval;
	}

	bool Counter::PastInterval()
	{
		if (myTime >= myInterval)
		{
			myTime = 0.0f;
			return true;
		}
		return false;
	}

	void Counter::Tick()
	{
		myTime += Timer::GetInstance()->TGetDeltaTime();
	}
}
