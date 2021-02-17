#pragma once
namespace Studio
{
	class Health
	{
	public:
		Health() = default;
		Health(float aMaxHealth);

		void TakeDamage(const float aDamageAmount);

		const float GetMaxHealth();
		const float GetCurrentHealth();
		const bool IsDead();

		bool GetGodMode();
		void SetGodMode(bool aChoice);
		void ResetHealth();
		void SetStartHealth(const float aHealthValue);
	private:
		float myMaxHealth = 0;
		float myCurrentHealth = 0;
		bool myIsDead = false;
		bool myIsGodMode = false;
	};
}
