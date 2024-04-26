#pragma once
#include "STD_Headers.h"
#include "types.h"
#include "enums.h"

class State;
class Monster;

class AI
{
public:
	AI();
	virtual ~AI();

public:
	void		Update();
	void		AddState(State* state);

private:
	Monster*	GetOwner()					{ return _owner; }
	void		SetOwner(Monster* mon)		{ _owner = mon; }
	State*		GetCurState()				{ return _curState; }
	void		SetCurState(State* state)	{ _curState = state; }
	State*		FindState(MONSTER_STATE key)
	{
		auto iter = _mapState.find(key);
		if (nullptr != (*iter).second)
		{
			return (*iter).second;
		}
		else return nullptr;
	}
	friend		class Monster;

private:
	Monster*					_owner		= nullptr;
	State*						_curState	= nullptr;
	map<MONSTER_STATE, State*>	_mapState;
};

