#pragma once

namespace Studio
{
	namespace Enums
	{
		enum class MovementPattern
		{
			None,
			Straight,
			Wave,
			Diagonal,
			Bobbing,
			UTurn,
			Homing,
			Seeking,
			Count
		};

		enum class BulletOwner
		{
			Player,
			Enemy,
			Boss,
			None
		};

		enum class RapidFireUpgrades
		{
			CooldownT1,
			AttackSpeedT1,
			AttackSpeedT2,
			DurationT1,
			DurationT2,
			PenetratingT3
			
		};

	}
}
