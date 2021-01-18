#pragma once
namespace Studio
{
	class Health
	{
	public: 
		Health() = default;
		Health(float aMaxHealth);

		void TakeDamage(float aDamageAmount);

		float GetMaxHealth();
		float GetCurrentHealth();
		const bool IsDead();

		void SetGodMode();
	private:
		float myMaxHealth = 0;
		float myCurrentHealth = 0;
		bool myIsDead = false;
		bool myIsGodMode = false;
	};
}
