#pragma once
#include "Component.h"

class InputHandler : public Component
{
public:
	InputHandler();
	~InputHandler() override;

public:
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Init()		override;

};

