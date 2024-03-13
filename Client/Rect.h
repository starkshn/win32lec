#pragma once
#include "Object.h"

class Rect : public Object
{
public:
	Rect();
	~Rect() override;

public:
	virtual void Update() override;
	virtual void Render() override;
};

