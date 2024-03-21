#include "pch.h"
#include "CollisionManager.h"
#include "Object.h"

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::Init()
{

}

void CollisionManager::Update()
{
	for (UINT row = 0; row < (UINT)OBJECT_TYPE::END; ++row)
	{
		for (UINT col = row; col < (UINT)OBJECT_TYPE::END; ++col)
		{
			if (_collisionCheck[row] & (1 << col))
			{
				CheckObjectsCollision(OBJECT_TYPE(row), (OBJECT_TYPE)col);
			}
		}
	}
}

void CollisionManager::CheckObjectsCollision(OBJECT_TYPE ltype, OBJECT_TYPE rtype)
{
	shared_ptr<Scene> curScene = SCENE->GetCurrentScene();

	const vector<shared_ptr<Object>>& rowObjs = curScene->GetObjectsByType(ltype);
	const vector<shared_ptr<Object>>& colObjs = curScene->GetObjectsByType(rtype);
	
	for (UINT i = 0; i < rowObjs.size(); ++i)
	{
		// nullptr�̰ų� �浹ü�� ���� ���
		if (rowObjs[i]->GetCollider() == nullptr || rowObjs[i] == nullptr)
			continue;

		for (UINT j = 0; j < colObjs.size(); ++j)
		{
			// nullptr�̰ų� �浹ü�� ���� ���
			if (colObjs[i]->GetCollider() == nullptr || colObjs[j] == nullptr)
				continue;

			// ���� �迭�� ��� (���� �׷�� ���ڽ��� �׷��� ���ϴ� ��� �ǳʶپ���Ѵ�)
			if (rowObjs == colObjs) 
				continue;
			
			if (IsEnterCollision(rowObjs[i]->GetCollider(), colObjs[j]->GetCollider()))
			{
				
			}
			else
			{

			}
		}
	}
}

void CollisionManager::UpdateObjectsCollision(OBJECT_TYPE ltype, OBJECT_TYPE rtype)
{

}

bool CollisionManager::IsEnterCollision(shared_ptr<Collider> left, shared_ptr<Collider> right)
{
	




	return false;
}

bool CollisionManager::IsOverlapCollision(shared_ptr<Collider> left, shared_ptr<Collider> right)
{

	return false;
}

bool CollisionManager::IsEndCollision(shared_ptr<Collider> left, shared_ptr<Collider> right)
{

	return false;
}


void CollisionManager::SetObjectCollisionByType(OBJECT_TYPE ltype, OBJECT_TYPE rtype)
{
	UINT row = UINT(ltype);
	UINT col = UINT(rtype);

	if (col < row)
	{
		row = UINT(rtype);
		col = UINT(ltype);
	}

	if (_collisionCheck[row] & (1 << col))
	{
		_collisionCheck[row] &= ~(1 << col);
	}
	else
	{
		_collisionCheck[row] |= (1 << col);
	}
}

void CollisionManager::ResetObjectCollision()
{
	memset(_collisionCheck, 0, sizeof(UINT) * (UINT)OBJECT_TYPE::END);
}

