#pragma once
namespace Studio
{
	class Counter
	{
	public:

		void SetInterval(const float anInterval);
		bool PastInterval();
		void Tick();
		const float GetTime() const;

	private:
		float myTime = 0.0f;
		float myInterval;
	};
}