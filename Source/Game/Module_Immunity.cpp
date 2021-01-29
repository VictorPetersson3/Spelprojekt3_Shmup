#include "stdafx.h"
#include "Module_Immunity.h"

Studio::Module_Immunity::Module_Immunity(rapidjson::Value& aModuleParameters) :
	Module(aModuleParameters)
{
}

bool Studio::Module_Immunity::DoStuff()
{
	return false;
}
