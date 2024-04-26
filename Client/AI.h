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

public:
	State*		GetCurState()				
	{
		if (nullptr != _curState) return _curState;
		return nullptr;
	}
	void		SetCurState(State* state)	{ _curState = state; }

private:
	Monster*	GetOwner()					{ return _owner; }
	void		SetOwner(Monster* mon)		{ _owner = mon; }

public:
	State*		FindState(MONSTER_STATE key)
	{
		auto iter = _mapState.find(key);
		if (iter != _mapState.end())
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

