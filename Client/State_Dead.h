#pragma once
#include "State.h"

class State_Dead : public State
{
public:
	State_Dead();
	virtual ~State_Dead() override;
	
public:
	virtual void Update() override;

public:
	virtual void StartState()	override;
	virtual void EndState()		override;
};

