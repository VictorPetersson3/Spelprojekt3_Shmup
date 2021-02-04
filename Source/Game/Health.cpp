#include "stdafx.h"
#include "Health.h"

Studio::Health::Health(float aMaxHealth) :
	myMaxHealth(aMaxHealth),
	myCurrentHealth(aMaxHealth)
{}

void Studio::Health::TakeDamage(const float aDamageAmount)
{
	if (!myIsGodMode)
	{
		if (!myIsDead)
		{
			myCurrentHealth -= aDamageAmount;
		}
		if (myCurrentHealth <= 0)
		{
			myIsDead = true;
		}
	}
}

const float Studio::Health::GetMaxHealth()
{
	return myMaxHealth;
}

const float Studio::Health::GetCurrentHealth()
{
	return myCurrentHealth;
}

const bool Studio::Health::IsDead()
{
	return myIsDead;
}
bool Studio::Health::GetGodMode()
{
	return myIsGodMode;
}
//Call Function to activate if deactivated and vice versa.
void Studio::Health::SetGodMode(bool aChoice)
{
	myIsGodMode = aChoice;
}

void Studio::Health::ResetHealth()
{
	myCurrentHealth = myMaxHealth;
	myIsDead = false;
}
