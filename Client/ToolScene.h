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
	void UpdateTextOfGameInfo();
	void RenderTextOfGameInfo();
	void RenderTextOfSceneInfo();

public:
	void ChangeTileIndex();

	static void SaveTileRelativePath(const wstring& relativePath);
	static void SaveTileAbsolutPath(const wstring& absolutePath);
	static void LoadTileRelativePath(const wstring& relativePath);
	static void LoadTileAbsolutePath(const wstring& relativePath);

	
// test
public:
	void Test() 
	{
		Vec2 pos = _testBTN->GetPos();
		Vec2 scale = _testBTN->GetScale();
		TextOut(GET_MEMDC, int32(300.f), int32(300.f), L"Click", 5);
	};

private:
	UI*		_temp			= nullptr;
	UI*		_toolUI			= nullptr;
	Vec2	_resolution		= Vec2(0.f, 0.f);
	UI*		_testBTN		= nullptr;
	vector<wstring> _vecGameInfoTexts;
};