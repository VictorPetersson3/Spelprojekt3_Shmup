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

		enum class Tier1Upgrades
		{
			RapidFireCooldown,
			RapidFireAttackSpeed,
			RapidFireDuration,

			BasicAttackSpeed,

			MissileExplosionRadius,
			MissileCooldown,
			MissileDamage,

			ShieldDuration,
			ShieldHealth,
			ShieldCooldown
		};
		enum class Tier2Upgrades
		{
			RapidFireAttackSpeed,
			RapidFireDuration,

			BasicAttackSpeed,
			BasicAttackAdditionalProjectile,

			MissileExplosionRadius,
			MissileCooldown,
			MissileDamage,

			ShieldDuration,
			ShieldHealth,
			ShieldCooldown
		};
		enum class Tier3Upgrades
		{
			RapidFirePenetrating,

			BasicAttackSpeed,

			MissileCluster,

			ShieldExplosion
		};

		// InputManager
		// ============
		// Note that enum class is not used.
		// That is because I do not want to force us to use 
		// static_cast<int> all the time when using the
		// input manager when checking for custom keys
		enum CustomKeys {
			CustomKey_None = 0,
			CustomKey_FlyUp,
			CustomKey_FlyDown,
			CustomKey_FlyRight,
			CustomKey_FlyLeft,
			CustomKey_RapidFire,
			CustomKey_Explosive,
			CustomKey_Shield,
			CustomKey_Shoot,
			CustomKey_Pause,
			CustomKey_Count
		};

		enum class PowerUpModules
		{
			BasicAttackFirst,
			BasicAttackSecond,
			RapidFire,
			Shield
		};

		// TODO: Remove this
		enum class Cutscene
		{
			Logos,
			Intro,
			Outro
		};

		enum class Video
		{
			Logos,
			Intro,
			Outro
		};

		enum class EParticleTypes
		{
			eRain,
			eSnow
		};
	}
}
