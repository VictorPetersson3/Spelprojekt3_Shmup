#include "stdafx.h"
#include "Health.h"

Studio::Health::Health(float aMaxHealth) :
	myMaxHealth(aMaxHealth),
	myCurrentHealth(aMaxHealth)
{}

void Studio::Health::TakeDamage(float aDamageAmount)
{
	if (!myIsGodMode)
	{
		myCurrentHealth -= aDamageAmount;
		if (myCurrentHealth <= 0)
		{
			myIsDead = true;
		}
	}
}

float Studio::Health::GetMaxHealth()
{
	return myMaxHealth;
}

float Studio::Health::GetCurrentHealth()
{
	return myCurrentHealth;
}

const bool Studio::Health::IsDead()
{
	return myIsDead;
}
//Call Function to activate if deactivated and vice versa.
void Studio::Health::SetGodMode()
{
	myIsGodMode = !myIsGodMode;
}