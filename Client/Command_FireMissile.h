#pragma once
#include "Command.h"

class Command_FireMissile : public Command
{
public:
	Command_FireMissile();
	~Command_FireMissile() override;

public:
	void Execute(UnitObject& unitObject) override;
};

