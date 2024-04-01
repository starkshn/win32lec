#pragma once
#include "Component.h"
class ChildComponent : public Component
{
public:
	ChildComponent();
	virtual ~ChildComponent() override;

public:
	virtual void Update() abstract;
	virtual void Render() abstract;
	virtual void Init() abstract;

public:
	Component* GetOwnerComp() { return _ownerComp; }
	void SetOwnerComp(Component* comp) { _ownerComp = comp; }

protected:
	Component* _ownerComp = nullptr;
};

