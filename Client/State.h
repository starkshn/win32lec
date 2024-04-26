#pragma once

class AI;

class State
{
public:
	State(MONSTER_STATE state);
	virtual ~State();

public:
	virtual void Update() {};

public:
	AI*					GetOwnerAI()			{ return _owner; }
	void				SetOwnerAI(AI* ai)		{ _owner = ai; }
	MONSTER_STATE		GetState()				{ return _curState; }
	void				SetState(MONSTER_STATE state) { _curState = state; }
	
public:
	virtual void		StartState()	{}
	virtual void		EndState()		{}

private:
	AI*					_owner		= nullptr;
	MONSTER_STATE		_curState	= MONSTER_STATE::NONE;
};

