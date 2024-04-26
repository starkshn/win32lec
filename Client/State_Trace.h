#pragma once
#include "State.h"
class State_Trace : public State
{
public:
	State_Trace();
	virtual ~State_Trace() override;

public:
	virtual void Update() override;

public:
	virtual void StartState()	override;
	virtual void EndState()		override;
};

