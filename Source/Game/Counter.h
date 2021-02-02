#pragma once
namespace Studio
{
	class Counter
	{
	public:

		void SetInterval(const float anInterval);
		bool PastInterval();
		void Tick();

	private:
		float myTime = 0.0f;
		float myInterval;
	};
}