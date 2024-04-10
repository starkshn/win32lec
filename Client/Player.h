#pragma once
#include "Object.h"
#include "UnitObject.h"
#include "ProjectileLine.h"

class Texture;

class Player : public UnitObject
{
public:
	Player();
	~Player() override;

	virtual Player* Clone() override;

public:
	virtual void Update() override;
	virtual void Render() override;
	virtual void Init() override;
	virtual void Begin() override;
	virtual void End() override;

public:
	virtual void Attack() override;

private:
	// Update key input มฆวั
	void DisMovement();
	void MoveWASD();
	void AngryMove();

public:
	void CreateProjectile();

private:
	ProjectileLine*			_projLine = nullptr;
	Vec2					_projDir = {1, 0};
};

