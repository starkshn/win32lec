#pragma once
#include "Manager.h"

// forward declarations...
class Scene;
class Object;
class Tile;

class BoardManager : public Manager
{
	DECLARE_SINGLE(BoardManager);

public:
	void Init() override;
	void Update() override;

public:
	Vec2 GetCurSceneBoardXYCounts() { return _curSceneBoardXYCount; }
	void SetCurSceneBoardXYCounts(Vec2 count)
	{
		_curSceneBoardXYCount = count;
	}

	Tile* GetTileObjectByTileID(int32 id);

private:
	void GenerateBoard_Kruskal();
	void GenerateBoard_Prim();

private:
	Scene*	_curScene = nullptr;
	Vec2	_curSceneBoardXYCount = Vec2(0.f, 0.f);
};

