#pragma once
#include "Object.h"

class GameObject : public Object
{
public:
	GameObject();
	virtual ~GameObject() override;

	virtual GameObject* Clone() override;

public:
	virtual void Update() override;
	virtual void Render() override;
	virtual void Init() override;
	virtual void Begin() override;
	virtual void End() override;
};

