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
			myTime -= myInterval;
			return true;
		}
		return false;
	}

	void Counter::Tick()
	{
		myTime += Timer::GetInstance()->TGetDeltaTime();
	}
	const float Counter::GetTime() const
	{
		return myTime;
	}
}