#pragma once
#include "Object.h"
#include "GameObject.h"

class UnitObject : public GameObject
{
public:
	UnitObject();
	~UnitObject() override;

	UnitObject* Clone() override;

public:
	virtual void Update() override;
	virtual void Render() override;
	virtual void Init() override;
	virtual void Begin() override;
	virtual void End() override;

public:
	virtual void Attack() abstract;
};

