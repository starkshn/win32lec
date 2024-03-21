#include "pch.h"
#include "CollisionManager.h"
#include "Object.h"
#include "Collider.h"

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
	map<ULONGLONG, bool>::iterator iter;

	
	for (UINT i = 0; i < rowObjs.size(); ++i)
	{
		// nullptr�̰ų� �浹ü�� ���� ���
		if (rowObjs[i]->GetCollider() == nullptr || rowObjs[i] == nullptr)
			continue;

		shared_ptr<Collider> rowCollider = rowObjs[i]->GetCollider();

		for (UINT j = 0; j < colObjs.size(); ++j)
		{
			// nullptr�̰ų� �浹ü�� ���� ���
			if (colObjs[j]->GetCollider() == nullptr || colObjs[j] == nullptr)
				continue;

			shared_ptr<Collider> colCollider = colObjs[j]->GetCollider();

			// ���� �迭�� ��� (���� �׷�� ���ڽ��� �׷��� ���ϴ� ��� �ǳʶپ���Ѵ�)
			if (rowObjs == colObjs) 
				continue;

			// union�� ���� ID�� ����� ����.
			COLLIDER_ID id;
			id._leftID	= rowCollider->GetID();
			id._rightID = colCollider->GetID();

			iter = _collisionInfo.find(id.ID);

			// end��� ���� ���� �����ӿ� �浹�� ���� ���ٴ� ���̴�.
			// �浹�� ���� �ְ� ���� ���� �˻縦 �ߴٸ� map�� ����� ���� �����Ѵ�.
			if (iter == _collisionInfo.end())
			{
				_collisionInfo.insert(make_pair(id.ID, false));
				iter = _collisionInfo.find(id.ID);
			}
			
			// �浹�ϴ� ���
			if (IsCollision(rowCollider, colCollider))
			{
				// �������� �浹���̴�.
				if (iter->second == true)
				{
					rowCollider->OnCollision(colCollider);
					colCollider->OnCollision(rowCollider);
					iter->second = true;
				}
				// �������� �浹���� �ʾҴ�.
				// ���ʷ� �浹
				else
				{
					rowCollider->OnCollisionEnter(colCollider);
					colCollider->OnCollisionEnter(rowCollider);
					iter->second = true;
				}
			}
			else
			{
				// ���� �浹�ϰ� ���� �ʴ�.
				// �浹���� �� ��� ����
				if (iter->second)
				{
					// �������� �浹�ϰ� �־���.
					rowCollider->OnCollisionExit(colCollider);
					colCollider->OnCollisionExit(rowCollider);
					iter->second = false;
				}
			}
		}
	}
}

void CollisionManager::UpdateObjectsCollision(OBJECT_TYPE ltype, OBJECT_TYPE rtype)
{

}

bool CollisionManager::IsCollision(shared_ptr<Collider> left, shared_ptr<Collider> right)
{
	Vec2 lPos = left->GetFinalPos();
	Vec2 lScale = left->GetColliderScale();

	Vec2 rPos = right->GetFinalPos();
	Vec2 rScale = right->GetColliderScale();

	if (abs(rPos.x - lPos.x) < (rScale.x + rScale.x) / 2.f && abs(rPos.y - lPos.y) < (rScale.y + lScale.y) / 2.f)
	{
		return true;
	}

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

