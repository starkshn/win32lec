#pragma once

class Collider;

class CollisionManager : public Manager
{
	DECLARE_SINGLE(CollisionManager);

public:
	void Init() override;
	void Update() override;
	void SetObjectCollisionByType(OBJECT_TYPE ltype, OBJECT_TYPE rtype);
	void ResetObjectCollision();

private:
	void CheckObjectsCollision(OBJECT_TYPE ltype, OBJECT_TYPE rtype);
	void UpdateObjectsCollision(OBJECT_TYPE ltype, OBJECT_TYPE rtype);

private:
	bool IsEnterCollision(shared_ptr<Collider> left, shared_ptr<Collider> right);
	bool IsOverlapCollision(shared_ptr<Collider> left, shared_ptr<Collider> right);
	bool IsEndCollision(shared_ptr<Collider> left, shared_ptr<Collider> right);

private:
	UINT _collisionCheck[UINT(OBJECT_TYPE::END)];
	
	// 충돌체간의 이전 프레임 정보
	
};

