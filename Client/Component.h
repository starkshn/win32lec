#pragma once
#include "pch.h"

class Object;

class Component
{
public:
	Component();
	virtual ~Component();

	Component(const Component& other);

private:
	Component& operator =	(Component& origin) = delete;
	Component& operator ==	(Component& origin) = delete;

public:
	virtual void Update();// 오브젝트의 위치를 따라간다.
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

	// renderPos
	const Vec2 GetCompRenderPos();
	
	void SetRenderPos(Vec2 pos) { _renderPos = pos; }
	const Vec2 GetRenderPos() { return _renderPos; }

private:
	Object*		_ownerObject	= nullptr;
	Vec2		_offset			= Vec2(0, 0);
	Vec2		_finalPos		= Vec2(0, 0);
	Vec2		_scale			= Vec2(10, 10);
	Vec2		_renderPos		= Vec2(-0.01f, -0.01f);
	bool		_visiable		= true;
};

