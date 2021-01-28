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
	}
}
