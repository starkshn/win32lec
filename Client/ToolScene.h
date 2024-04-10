#pragma once
#include "Scene.h"

class ToolScene : public Scene
{
public:
	ToolScene();
	virtual ~ToolScene() override;

public:
	virtual void InitScene() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void BeginScene() override;
	virtual void EndScene() override;	

public:
	void ChangeTileIndex();
};