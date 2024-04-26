#pragma once
#include "Object.h"
#include "UnitObject.h"

class AI;

class Monster : public UnitObject
{

public:
	Monster();
	~Monster() override;
	virtual Monster* Clone() override
	{
		return new Monster(*this);
	}

public:
	virtual void	Update() override;
	virtual void	Render() override;
	virtual void	Init() override;
	virtual void	Begin() override;
	virtual void	End() override;

public:
	virtual void	Attack() override;

public:
	virtual void	OnCollision(Collider* otherCollider) override;
	virtual void	OnCollisionEnter(Collider* otherCollider) override;
	virtual void	OnCollisionExit(Collider* otherCollider) override;

public:
	AI*				GetModuleAI()		{ return _moduleAI; }
	void			SetModuleAI(AI* ai);

private:
	AI*			_moduleAI	= nullptr;
};

