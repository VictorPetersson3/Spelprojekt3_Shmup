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
	myStartPosition = { 0.0f, 0.0f };
	if (aModuleParameters.HasMember("Type"))
	{
		std::string type = aModuleParameters["Type"].GetString();
		if (type == "Bobbing")
		{
			float speed;
			float height;

			speed = aModuleParameters["Speed"].GetFloat();
			height = aModuleParameters["Height"].GetFloat();
			SAFE_CREATE(myModuleMovement, MovementBobbing(&myStartPosition, speed, height));
		}
		else if (type == "Straight")
		{
			float speed;

			speed = aModuleParameters["Speed"].GetFloat();

			SAFE_CREATE(myModuleMovement, MovementStraight(&myStartPosition, speed));
		}
		else if (type == "Wave")
		{
			float horizontal;
			float vertical;
			float height;

			horizontal = aModuleParameters["HorizontalSpeed"].GetFloat();
			vertical = aModuleParameters["VerticalSpeed"].GetFloat();
			height = aModuleParameters["Height"].GetFloat();

			SAFE_CREATE(myModuleMovement, MovementWave(&myStartPosition, horizontal, vertical, height));
		}
		else if (type == "Diagonal")
		{
			printf("Tell Pu to implement the Diagonal Movement if LD wants it\n");
		}
		else
		{
			printf("This Movement: %s is not implemented in boss. \n", aModuleParameters["Type"].GetString());
		}
	}
	myHasSetStartPos = false;
}

Studio::Module_Movement::~Module_Movement()
{
	SAFE_DELETE(myModuleMovement);
}

bool Studio::Module_Movement::DoStuff(Boss& aBoss)
{
	if (!myHasSetStartPos)
	{
		myModuleMovement->SetMovementStartPosition(aBoss.GetPositionPointer());
	}
	aBoss.UpdateMovement(myModuleMovement);
	//printf("Changed Movement\n");
	return true;
}
