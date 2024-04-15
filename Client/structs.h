#pragma once
#include "types.h"

struct PQNode
{
	bool operator < (const PQNode& other) const
	{
		return f < other.f;
	}

	bool operator > (const PQNode& other) const
	{
		return f > other.f;
	}

	int32	f; // f = g + h
	int32	g;
	Vec2	pos;
};

struct CostEdge
{
	int		cost;
	Vec2	u;
	Vec2	v;

	bool operator < (const CostEdge& other) const
	{
		return cost < other.cost;
	}
};

struct NodeForAStar
{
	bool operator < (const NodeForAStar& other) const
	{
		return f < other.f;
	}

	bool operator > (const NodeForAStar& other) const
	{
		return f > other.f;
	}

	int32	f; // f = g + h
	int32	g;
	int32	id;
};

struct PrimCostEdge
{
	int		_cost;
	Vec2	_vertex;

	bool operator < (const PrimCostEdge& other) const
	{
		return _cost < other._cost;
	}
};

struct DIR_BOARD
{

	// 단순 방향 벡터 반환
	Vec2 Left() { return _left; }
	Vec2 Down() { return _down; }
	Vec2 Right() { return _right; }
	Vec2 Up() { return _up; }

	Vec2 LeftUp() { return _leftUp; }
	Vec2 leftDown() { return _leftDown; }
	Vec2 RightDown() { return _rightDown; }
	Vec2 RightUp() { return _rightUp; }

	
	// ID
	int32 GetLeftIdx(int32 idx) { return idx - 1; }
	int32 GetRightIdx(int32 idx) { return idx + 1; }
	int32 GetDownIdx(int32 idx, int32 boardMaxX, int32 boardMaxY)
	{ 
		int32 curY = idx / boardMaxX;
		int32 curX = idx % boardMaxX;
		return (boardMaxX * (curY + 1) + curX);
	}
	int32 GetUpIdx(int32 idx, int32 boardMaxX, int32 boardMaxY)
	{
		int32 curY = idx / boardMaxX;
		int32 curX = idx % boardMaxX;
		return (boardMaxX * (curY -1 ) + curX);
	}

	int32 GetDirIdx(int32 dir, int32 curIdx, int32 boardX, int32 boardY)
	{
		if (dir == 0) return GetLeftIdx(curIdx);
		else if (dir == 1) return GetDownIdx(curIdx, boardX, boardY);
		else if (dir == 2) return GetRightIdx(curIdx);
		else if (dir == 3) return GetUpIdx(curIdx, boardX, boardY);
		else return -1;
	}

private:
	Vec2 _left = Vec2{ -1, 0 };
	Vec2 _down = Vec2{ 0, 1 };
	Vec2 _right = Vec2{ 1, 0 };
	Vec2 _up = Vec2{ 0, -1 };

	Vec2 _leftUp = Vec2{ -1, -1 };
	Vec2 _leftDown = Vec2{ -1, 1 };
	Vec2 _rightDown = Vec2{ 1, -1 };
	Vec2 _rightUp = Vec2{ 1, 1 };
};


