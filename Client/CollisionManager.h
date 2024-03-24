#pragma once

class Collider;

union COLLIDER_ID
{
	struct
	{
		UINT _leftID;
		UINT _rightID;
	};

	ULONGLONG ID;
};

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
	bool IsCollision(Collider* left, Collider* right);
	bool IsOverlapCollision(Collider* left, Collider* right);
	bool IsEndCollision(Collider* left, Collider* right);

private:
	UINT _collisionCheck[UINT(OBJECT_TYPE::END)];
	
	// 이전 프레임 충돌 정보
	map<ULONGLONG, bool> _collisionInfo;
};

