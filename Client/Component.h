#pragma once

class Object;

class Component
{
public:
	Component();
	~Component();

	Component(const Component& other);

private:
	Component& operator =	(Component& origin) = delete;
	Component& operator ==	(Component& origin) = delete;

public:
	virtual void FinalUpdate();// 오브젝트의 위치를 따라간다.
	virtual void Render();
	virtual void Init() {};

public:
	// owner obj
	Object* GetOwnerObject() { return _ownerObject; }
	void SetOwnerObject(Object* obj) { _ownerObject = obj; }

	void SetVisible() { _visiable = true; }
	void SetNotVisible() { _visiable = false; }
	bool GetVisibility() const { return _visiable; }
	
	// offset
	const Vec2 GetOffset() { return _offset; }
	void SetOffset(Vec2 offset) { _offset = offset; }

	// final pos
	const Vec2 GetFinalPos() { return _finalPos; }
	void SetFinalPos(Vec2 pos) { _finalPos = pos; }

	// scale
	const Vec2 GetScale() { return _scale; }
	void SetScale(Vec2 scale) { _scale = scale; }

private:
	Object*		_ownerObject	= nullptr;
	Vec2		_offset			= Vec2(0, 0);
	Vec2		_finalPos		= Vec2(0, 0);
	Vec2		_scale			= Vec2(10, 10);
	bool		_visiable		= true;
};

