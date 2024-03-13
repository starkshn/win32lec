#pragma once
#include "Rect.h"
class Brick : public Rect
{
public:
	Brick();
	~Brick() override;

public:
	virtual void Update() override;
	virtual void Render() override;
};

