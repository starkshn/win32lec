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
	Scene* curScene = SCENE->GetCurrentScene();

	const vector<Object*>& rowObjs = curScene->GetObjectsByType(ltype);
	const vector<Object*>& colObjs = curScene->GetObjectsByType(rtype);

	unordered_map<ULONGLONG, bool>::iterator iter;

	for (UINT i = 0; i < rowObjs.size(); ++i)
	{
		if (rowObjs[i]->GetCollider() == nullptr || rowObjs[i] == nullptr)
			continue;

		Object* rowObj = rowObjs[i];
		Collider* rowCollider = rowObjs[i]->GetCollider();

		for (UINT j = 0; j < colObjs.size(); ++j)
		{
			if (colObjs[j]->GetCollider() == nullptr || colObjs[j] == nullptr)
				continue;

			Object* colObj = colObjs[j];
			Collider* colCollider = colObjs[j]->GetCollider();

			// 같은 배열인 경우 (나의 그룹과 나자신의 그룹을 비교하는 경우 건너뛰어야한다)
			if (rowObjs == colObjs)
				continue;

			// union을 통해 ID를 만들어 낸다.
			COLLIDER_ID id;
			id._leftID = rowCollider->GetID();
			id._rightID = colCollider->GetID();

			// TODO
			// std::map 말고 HashTable로 O(1)로 찾을 수 있도록 나중에 수정하자.
			iter = _unmapCollisionInfo.find(id.ID);

			// end라는 말은 이전 프레임에 충돌한 적이 없다는 말이다.
			// 충돌을 한적 있건 없건 간에 검사를 했다면 map에 등록을 시켜 놔야한다.
			if (iter == _unmapCollisionInfo.end())
			{
				_unmapCollisionInfo.insert(make_pair(id.ID, false));
				iter = _unmapCollisionInfo.find(id.ID);
			}

			// 충돌하는 경우
			if (IsCollision(rowCollider, colCollider))
			{
				// 현재 충돌중이다.

				// 이전에도 충돌중이다.
				if (iter->second == true)
				{
					// 삭제될 예정인 경우
					if (rowObj->GetThisObjectWillDelete() || colObj->GetThisObjectWillDelete())
					{
						rowCollider->OnCollisionExit(colCollider);
						colCollider->OnCollisionExit(rowCollider);
						iter->second = false;
					}
					// 삭제될 예정인 경우가 아니라면
					else
					{
						rowCollider->OnCollision(colCollider);
						colCollider->OnCollision(rowCollider);
						iter->second = true;
					}
				}
				else
				{
					// 이전에는 충돌하지 않았다.
					// 최초로 충돌하는 경우이다.

					// 삭제될 예정인 경우가 둘다 아닐 경우
					if (!rowObj->GetThisObjectWillDelete() && !colObj->GetThisObjectWillDelete())
					{
						rowCollider->OnCollisionEnter(colCollider);
						colCollider->OnCollisionEnter(rowCollider);
						iter->second = true;
					}
				}
			}
			else
			{
				// 현재 충돌하고 있지 않다.
				// 충돌에서 막 벗어난 시점
				if (iter->second)
				{
					// 이전에는 충돌하고 있었다.
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

bool CollisionManager::IsCollision(Collider* left, Collider* right)
{
	Vec2 lPos = left->GetFinalPos();
	Vec2 lScale = left->GetScale();

	Vec2 rPos = right->GetFinalPos();
	Vec2 rScale = right->GetScale();

	if (abs(rPos.x - lPos.x) < (rScale.x + rScale.x) / 2.f && abs(rPos.y - lPos.y) < (rScale.y + lScale.y) / 2.f)
	{
		return true;
	}

	return false;
}

bool CollisionManager::IsOverlapCollision(Collider* left, Collider* right)
{
	return false;
}

bool CollisionManager::IsEndCollision(Collider* left, Collider* right)
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

