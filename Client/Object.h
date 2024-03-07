#pragma once

#define GL GetLeft()
#define GT GetTop()
#define GR GetRight()
#define GB GetBottom()

class Object
{
public:
	Object();
	~Object();

public:
	void SetPos(Vec2 pos) { _pos = pos; }
	void SetScale(Vec2 scale) { _scale = scale; }

	Vec2 GetPos() { return _pos; }
	Vec2 GetScale() { return _scale; }

public:
	int GetLeft() { return _pos._x - _scale._x / 2; };
	int GetTop() { return _pos._y - _scale._y / 2; };
	int GetRight() { return _pos._x + _scale._x / 2; };
	int GetBottom() { return _pos._y + _scale._y / 2; };

private:
	Vec2 _pos = {};
	Vec2 _scale = {};
};

