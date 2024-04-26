#pragma once
#include "Scene.h"


class StartScene : public Scene
{
	
public:
	StartScene();
	virtual ~StartScene() override;

public:
	virtual void InitScene() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void BeginScene() override;
	virtual void EndScene() override;

protected:
	virtual void UpdateSceneKeyInput() override;
};

