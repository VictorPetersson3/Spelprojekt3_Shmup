#include "stdafx.h"
#include "Module_Movement.h"
#include "Movement.h"
#include "MovementBobbing.h"
#include "MovementDiagonal.h"
#include "MovementHoming.h"
#include "MovementSeeking.h"
#include "MovementStraight.h"
#include "MovementWave.h"

Studio::Module_Movement::Module_Movement(rapidjson::Value& aModuleParameters) :
	Module_Movement::Module(aModuleParameters)
{
	myStartPosition = { 1500.0f, 520.0f };
	if (aModuleParameters.HasMember("Type"))
	{
		std::string type = aModuleParameters["Type"].GetString();
		if (type == "Bobbing")
		{
			myVerticalSpeed = aModuleParameters["Speed"].GetFloat();
			myHeight = aModuleParameters["Height"].GetFloat();

			myMovementPattern = Enums::MovementPattern::Bobbing;
		}
		else if (type == "Straight")
		{
			mySpeed = aModuleParameters["Speed"].GetFloat();
			myMovementPattern = Enums::MovementPattern::Straight;
		}
		else if (type == "Wave")
		{
			myHorizontalSpeed = aModuleParameters["HorizontalSpeed"].GetFloat();
			myVerticalSpeed = aModuleParameters["VerticalSpeed"].GetFloat();
			myHeight = aModuleParameters["Height"].GetFloat();
			myMovementPattern = Enums::MovementPattern::Wave;
		}
		else if (type == "Diagonal")
		{
			printf("Tell Pu to implement the Diagonal Movement if LD wants it\n");
			myMovementPattern = Enums::MovementPattern::None;
		}
		else
		{
			printf("This Movement: %s is not implemented in boss. \n", aModuleParameters["Type"].GetString());
			myMovementPattern = Enums::MovementPattern::None;
		}
	}
	myHasSetStartPos = false;
	myHasChangedPhaseMovement = false;
}

Studio::Module_Movement::~Module_Movement()
{
	SAFE_DELETE(myModuleMovement);
}

bool Studio::Module_Movement::DoStuff(Boss& aBoss)
{
	if (!myHasChangedPhaseMovement)
	{
		switch (myMovementPattern)
		{
		case Studio::Enums::MovementPattern::Straight:
			aBoss.UpdateMovement(new MovementStraight(aBoss.GetPosition(), mySpeed));
			break;
		case Studio::Enums::MovementPattern::Wave:
			aBoss.UpdateMovement(new MovementWave(aBoss.GetPosition(), myHorizontalSpeed, myVerticalSpeed, myHeight));
			break;
		case Studio::Enums::MovementPattern::Diagonal:
			break;
		case Studio::Enums::MovementPattern::Bobbing:
			aBoss.UpdateMovement(new MovementBobbing(aBoss.GetPosition(), myVerticalSpeed, myHeight));
			break;
		default:
			break;
		}
		printf("Changed Movement\n");
		myHasChangedPhaseMovement = true;
	}
	return true;
}
