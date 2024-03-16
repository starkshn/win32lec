#pragma once
#include "Object.h"
#include "ProjectileLine.h"

class Player : public Object
{

public:
	virtual void Update() override;
	virtual void Render() override;
	virtual void Init() override;
	virtual void Begin() override;
	virtual void End() override;

private:
	// Update key input มฆวั
	void DisMovement();
	void MoveWASD();
	void AngryMove();

public:
	void CreateProjectile();

private:
	shared_ptr<Scene> _curScene = nullptr;
	SCENE_TYPE _curType;
	shared_ptr<ProjectileLine> _projLine = nullptr;
	Vec2 _projDir = {1, 0};
	
};

