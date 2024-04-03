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

			// ���� �迭�� ��� (���� �׷�� ���ڽ��� �׷��� ���ϴ� ��� �ǳʶپ���Ѵ�)
			if (rowObjs == colObjs)
				continue;

			// union�� ���� ID�� ����� ����.
			COLLIDER_ID id;
			id._leftID = rowCollider->GetID();
			id._rightID = colCollider->GetID();

			// TODO
			// std::map ���� HashTable�� O(1)�� ã�� �� �ֵ��� ���߿� ��������.
			iter = _unmapCollisionInfo.find(id.ID);

			// end��� ���� ���� �����ӿ� �浹�� ���� ���ٴ� ���̴�.
			// �浹�� ���� �ְ� ���� ���� �˻縦 �ߴٸ� map�� ����� ���� �����Ѵ�.
			if (iter == _unmapCollisionInfo.end())
			{
				_unmapCollisionInfo.insert(make_pair(id.ID, false));
				iter = _unmapCollisionInfo.find(id.ID);
			}

			// �浹�ϴ� ���
			if (IsCollision(rowCollider, colCollider))
			{
				// ���� �浹���̴�.

				// �������� �浹���̴�.
				if (iter->second == true)
				{
					// ������ ������ ���
					if (rowObj->GetThisObjectWillDelete() || colObj->GetThisObjectWillDelete())
					{
						rowCollider->OnCollisionExit(colCollider);
						colCollider->OnCollisionExit(rowCollider);
						iter->second = false;
					}
					// ������ ������ ��찡 �ƴ϶��
					else
					{
						rowCollider->OnCollision(colCollider);
						colCollider->OnCollision(rowCollider);
						iter->second = true;
					}
				}
				else
				{
					// �������� �浹���� �ʾҴ�.
					// ���ʷ� �浹�ϴ� ����̴�.

					// ������ ������ ��찡 �Ѵ� �ƴ� ���
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

