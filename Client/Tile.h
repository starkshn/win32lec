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
	Vec2 GetOffSet() { return _offset; }
	void SetOffSet(Vec2 offset) { _offset = offset; }

	void SetTileIdx(uint32 idx)
	{
		_tileIdx = idx;
	}
	uint32 GetTileIdx() { return _tileIdx; }

private:
	Texture*	_tileTexture	= nullptr;
	int32		_tileIdx		= 0;
	Vec2		_offset			= Vec2{0.f, 0.f};
};

