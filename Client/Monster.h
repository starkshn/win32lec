#pragma once
#include "Object.h"
class Monster : public Object
{

public:
	Monster();
	~Monster() override;

public:
	virtual void Update() override;
	virtual void Render() override;
	virtual void Init() override;
};

