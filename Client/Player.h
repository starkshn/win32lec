#pragma once
#include "Object.h"
#include "UnitObject.h"
#include "ProjectileLine.h"

class Texture;
class Tile;

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
	// Update key input 제한
	void DisMovement();
	void MoveWASD();

public:
	void CreateProjectile();

private:
	ProjectileLine*			_projLine = nullptr;
	Vec2					_projDir = {1, 0};

	// A*
public:
	void AStar();
	bool CanGo(int32 id, int32 boardX, int32 boardY);

public:
	int32	GetDestTileID()					{ return _destTileID.front(); }
	void	PushDestTileID(int32 id)		{ _destTileID.push(id); }
	void	PopFront()						{ _destTileID.pop(); }
	bool	QueueEmpty()					{ return _destTileID.empty(); }
	int32	GetPlayerCurTileID()			{ return _curTileID; }
	void	SetPlayerCurTileID(int32 id)	{ _curTileID = id; }

private:
	queue<int32>	_destTileID;
	int32			_curTileID = -1;
	// 경로를 담을 자료구조를 list를 써도 될 듯하다.
	vector<int32>	_pathTileID;

	float			_accTime = 0.f;
	int32			_pathIdx = 0;
};

