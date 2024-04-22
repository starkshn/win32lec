#pragma once

class UnitObject;

class Command
{
public:
	Command();
	virtual ~Command();

public:
	virtual void Execute(UnitObject& unitObject) abstract;
};

