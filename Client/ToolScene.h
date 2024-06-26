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
	virtual void UpdateSceneKeyInput() override;

private:
	void RenderTextOfToolSceneInfo();

public:
	void ChangeTileIndex();

public:
	static void SaveTileRelativePath(const wstring& relativePath);
	static void SaveTileAbsolutPath(const wstring& absolutePath);
	static void LoadTileRelativePath(const wstring& relativePath);
	static void LoadTileAbsolutePath(const wstring& relativePath);

private:
	UI*				_temp				= nullptr;
	UI*				_toolUI				= nullptr;
	UI*				_testBTN			= nullptr;
	Vec2			_resolution			= Vec2(0.f, 0.f);
};