#pragma once
namespace Studio
{

	class Ability
	{
	public:
		Ability();
		~Ability();

		void InitAbility();



	private:
		float myDamage;
		float myCooldown;

		VECTOR2F myDamageArea;
		VECTOR2F myEffectCenter;

	};

} 

