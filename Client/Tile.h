#pragma once
#include "GameObject.h"

// forward declration...
class Texture;

class Tile : public GameObject
{
public:
	Tile();
	~Tile() override;

	Tile* Clone() override;

public:
	virtual void Update() override;
	virtual void Render() override;
	virtual void Init() override;
	virtual void Begin() override;
	virtual void End() override;

public:
	virtual void Save(FILE* file);
	virtual void Load(FILE* file);

public:
	TILE_TYPE GetTileType() { return _tileTYpe; }
	void SetTileType(TILE_TYPE type) { _tileTYpe = type; }

	Vec2 GetOffSet() { return _offset; }
	void SetOffSet(Vec2 offset) { _offset = offset; }

	void SetTileIdx(uint32 idx)
	{
		_tileIdx = idx;
	}
	uint32 GetTileIdx() { return _tileIdx; }

	int32 GetTileID() { return _tileObjectID; }
	void SetTileID(int32 id) { _tileObjectID = id; }

private:
	Texture*	_tileTexture	= nullptr;
	TILE_TYPE	_tileTYpe		= TILE_TYPE::EMPTY;
	int32		_tileIdx		= 0;
	int32		_tileObjectID	= 0;
	Vec2		_offset			= Vec2{0.f, 0.f};

private:
	static	int32 g_tileObjectID;
};

