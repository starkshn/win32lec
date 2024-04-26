#pragma once

#include "Scene.h"

class MainMenuScene : public Scene
{
	
public:
	MainMenuScene();
	virtual ~MainMenuScene() override;

public:
	virtual void InitScene() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void BeginScene() override;
	virtual void EndScene() override;
	

protected:
	virtual void UpdateSceneKeyInput() override;
};

