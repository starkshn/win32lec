#pragma once

class Object;

class Collider
{
public:
	Collider();
	~Collider();

public:
	static UINT g_nextID;

public:
	// 오브젝트의 위치를 따라간다.
	void FinalUpdate();
	void Render();

public:
	shared_ptr<Object> GetOuterObject()
	{
		return _outerObject.lock();
	}
	void SetOuterObject(weak_ptr<Object> obj)
	{
		_outerObject = obj;
	}

	const Vec2 GetOffset() { return _offset; }
	void SetOffset(Vec2 offset) { _offset = offset; }

	const Vec2 GetFinalPos() { return _finalPos; }
	void SetFinalPos(Vec2 pos) { _finalPos = pos; }

	const Vec2 GetColliderScale() { return _colliderScale; }
	void SetColliderScale(Vec2 scale) { _colliderScale = scale; }

private:
	weak_ptr<Object> _outerObject;
	Vec2 _offset;	// 기준 위치로 부터 상대적인 거리값
	Vec2 _finalPos;
	Vec2 _colliderScale;

	UINT _id;
};

