#include "pch.h"
#include "Command_FireMissile.h"
#include "UnitObject.h"

Command_FireMissile::Command_FireMissile()
{

}

Command_FireMissile::~Command_FireMissile()
{

}

void Command_FireMissile::Execute(UnitObject& unitObject)
{
	unitObject.Attack();
}

