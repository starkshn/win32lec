#pragma once

#define GL GetLeft()
#define GT GetTop()
#define GR GetRight()
#define GB GetBottom()

class Object
{
public:
	Object();
	virtual ~Object();

public:
	void Update();
	void Render();

public:
	void SetPos(Vec2 pos) { _pos = pos; }
	void SetScale(Vec2 scale) { _scale = scale; }

	Vec2 GetPos() { return _pos; }
	Vec2 GetScale() { return _scale; }
	
public:
	// when OBJECT_TYPE is rectangle can use below functions
	int GetLeft() { return _pos.x - _scale.x / 2; };
	int GetTop() { return _pos.y - _scale.y / 2; };
	int GetRight() { return _pos.x + _scale.x / 2; };
	int GetBottom() { return _pos.y + _scale.y / 2; };

private:
	Vec2 _pos = {};
	Vec2 _scale = {};
};

