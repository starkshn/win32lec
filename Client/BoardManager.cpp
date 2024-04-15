#include "pch.h"
#include "BoardManager.h"
#include "Scene.h"
#include "Object.h"
#include "Tile.h"
#include "DisjointSet.h"
#include "structs.h"

BoardManager::BoardManager()
{}

BoardManager::~BoardManager()
{

}

void BoardManager::Init()
{
	_curScene = SCENE->GetCurrentScene();
	NULL_PTR_CHECK(_curScene);
	if (_curScene->GetOwnSceneType() != SCENE_TYPE::START) return;

	// ���� ���� Ÿ�� ���� �� �̷� �� ����
	_curScene->CreateTile(11, 11);
	SetCurSceneBoardXYCounts(Vec2(11.f, 11.f));

	// ���� �̷θ� ����
	GenerateBoard_Prim();
	// GenerateBoard_Kruskal();

	// Ÿ���� 1, 1 ��ġ ��ǥ ���ϰ� �÷��̾� ��ġ��Ű��
	Vec2 tileXYCount = BOARD->GetCurSceneBoardXYCounts();
	Tile* startTile =  static_cast<Tile*>(_curScene->GetObjectByTypeAndIndex(OBJECT_TYPE::DEFAULT_TILE, int32(tileXYCount.x * 1 + 1)));
	Vec2 startTilePos = startTile->GetPos();
	Vec2 playerStartPos = Vec2(startTilePos.x + TILE_SIZE / 2.f, startTilePos.y + TILE_SIZE / 2.f);

	GET_PLAYER->SetPlayerCurTileID(int32(tileXYCount.x * 1 + 1));
	GET_PLAYER->SetPos(playerStartPos);
}

void BoardManager::Update()
{

}

Tile* BoardManager::GetTileObjectByTileID(int32 id)
{
	Scene* curScene = SCENE->GetCurrentScene();
	NULL_PTR_CHECK(curScene);

	vector<Object*>& vecTiles = curScene->GetObjectsByType(OBJECT_TYPE::DEFAULT_TILE);

	IS_VALID_IDX(vecTiles, id);
	NULL_PTR_CHECK(vecTiles[id]);

	return static_cast<Tile*>(vecTiles[id]);
}

void BoardManager::GenerateBoard_Kruskal()
{
	::srand(unsigned(time(nullptr)));

	vector<Object*>& vecTiles = _curScene->GetObjectsByType(OBJECT_TYPE::DEFAULT_TILE);

	// ���� �� Ÿ�� X Y ���� ��������
	Vec2 counts = _curScene->GetCurrentTileXYCount();
	const int32 countX = int32(counts.x);
	const int32 countY = int32(counts.y);

	// N * N ���ڸ� ����� �� �θ��� 
	{
		// 2�� ������ �������� WALL�� ����
		for (int32 y = 0; y < countY; ++y)
		{
			for (int32 x = 0; x < countX; ++x)
			{
				uint32 tileIdx = countY * y + x;
				Tile* tile = static_cast<Tile*>(vecTiles[tileIdx]);
				NULL_PTR_CHECK(tile);

				if (x % 2 == 0 || y % 2 == 0)
				{
					tile->SetTileIdx(7);
					tile->SetTileType(TILE_TYPE::WALL);
				}
				else
				{
					tile->SetTileType(TILE_TYPE::EMPTY);
				}
			}
		}
	}
	

	vector<CostEdge> vecEdge;
	priority_queue<CostEdge> pq;

	// ������ ����ġ�� �������� �߰��ϰ� �̸� pq�� ����
	{
		// 2�� ������ �������� �ʴ� ������ ������ ����ġ ����
		for (int32 y = 0; y < countY; ++y)
		{
			for (int32 x = 0; x < countX; ++x)
			{
				if (x % 2 == 0 || y % 2 == 0)
					continue;

				// ������ �����ϴ� ���� �ĺ��� �����.
				if (x < countX - 2)
				{
					int32 randVal = ::rand() % 100;
					pq.push({ randVal, Vec2{float(x), float(y)}, Vec2{float(x + 2), float(y)} });
				}

				if (y < countY - 2)
				{
					int32 randVal = ::rand() % 100;
					pq.push({ randVal, Vec2{float(x), float(y)}, Vec2{float(x), float(y + 2)} });
				}
			}
		}
	}
	

	// ���Ͽ� ���ε� (Disjoint Set ��ü ����)
	DisjointSet sets(countY * countX);

	// ũ�罺Į ����
	{
		// pq�� �������� �Ʒ��� ������ �ݺ��Ѵ�.
		while (!pq.empty())
		{
			CostEdge now = pq.top(); pq.pop();
			int32 u = int32(now.u.y * countY) + int32(now.u.x);
			int32 v = int32(now.v.y * countY) + int32(now.v.x);

			// ���� �׷����� �ƴ��� Ȯ��
			if (sets.FindParent(u) == sets.FindParent(v)) continue;

			// ���� �׷��� �ƴ϶�� ��ģ��.
			sets.Merge(u, v);

			int32 y = int32((now.u.y + now.v.y) / 2.f);
			int32 x = int32((now.u.x + now.v.x) / 2.f);
			int32 idx = y * countY + x;
			Tile* tile = static_cast<Tile*>(vecTiles[idx]);

			tile->SetTileType(TILE_TYPE::EMPTY);
			tile->SetTileIdx(0);
		}
	}
}

void BoardManager::GenerateBoard_Prim()
{
	::srand(unsigned(time(nullptr)));

	vector<Object*>& vecTiles = _curScene->GetObjectsByType(OBJECT_TYPE::DEFAULT_TILE);

	// ���� �� Ÿ�� X Y ���� ��������
	Vec2 counts = _curScene->GetCurrentTileXYCount();
	const int32 countX = int32(counts.x);
	const int32 countY = int32(counts.y);

	// N * N ���ڸ� ����� �� �θ��� 
	{
		// 2�� ������ �������� WALL�� ����
		for (int32 y = 0; y < countY; ++y)
		{
			for (int32 x = 0; x < countX; ++x)
			{
				uint32 tileIdx = countY * y + x;
				Tile* tile = static_cast<Tile*>(vecTiles[tileIdx]);
				NULL_PTR_CHECK(tile);

				if (x % 2 == 0 || y % 2 == 0)
				{
					tile->SetTileIdx(7);
					tile->SetTileType(TILE_TYPE::WALL);
				}
				else
				{
					tile->SetTileType(TILE_TYPE::EMPTY);
				}
			}
		}
	}

	map<Vec2, vector<PrimCostEdge>> edges;

	// ������ ����ġ ����
	{
		// edges �ĺ��� ���� ����� ���� ������� �����Ѵ�.
		for (int32 y = 0; y < countY; ++y)
		{
			for (int32 x = 0; x < countX; ++x)
			{
				// WALL���� ���� ���� �ʷ� ���� �������� ����, �Ʒ� ��.
				if (x % 2 == 0 || y % 2 == 0)
					continue;

				// ������ �����ϴ� ���� �ĺ��� �����.
				if (x < countX - 2)
				{
					// [s] [��] [d] [��]
					const int32 randVal = ::rand() % 100;
					Vec2 u = Vec2{ float(x), float(y)};
					Vec2 v = Vec2{ float(x + 2), float(y) };
					edges[u].push_back(PrimCostEdge{ randVal, v });
					edges[v].push_back(PrimCostEdge{ randVal, u });
				}

				// �Ʒ��� �����ϴ� ���� �ĺ� �����
				if (y < countY - 2)
				{
					const int32 randVal = ::rand() % 100;
					Vec2 u = Vec2{ float(x), float(y)};
					Vec2 v = Vec2{ float(x), float(y + 2)};
					edges[u].push_back(PrimCostEdge{ randVal, v });
					edges[v].push_back(PrimCostEdge{ randVal, u });
				}
			}
		}
	}

	// Ž���� ������ Ʈ���� ���ԵǾ� �ִ��� Ȯ���� map
	map<Vec2, bool> added;

	// �����ϱ� ���� �뵵�� map
	map<Vec2, Vec2> parent;

	// �ּ� ���� ������ ���� map
	map<Vec2, int32> best;

	// �ʱ�ȭ �۾�
	for (int32 y = 0; y < countY; ++y)
	{
		for (int32 x = 0; x < countX; ++x)
		{
			best[Vec2{ float(x), float(y) }] = INT32_MAX;
			added[Vec2{ float(x), float(y)}] = false;
		}
	}

	priority_queue<PrimCostEdge> pq;
	Vec2 startPos = Vec2{ 1.f, 1.f };
	best[startPos] = 0;
	pq.push(PrimCostEdge{ 0, startPos });
	parent[startPos] = startPos;

	while (!pq.empty())
	{
		auto now = pq.top(); pq.pop();
		Vec2 nowPos = now._vertex;
		int32 nowCost = now._cost;

		if (added[nowPos]) continue;
		added[nowPos] = true;
		
		// �ʿ� ����
		{
			int32 x = int32((parent[nowPos].x + nowPos.x) / 2.f);
			int32 y = int32((parent[nowPos].y + nowPos.y) / 2.f);
			int32 tileIdx = countX * y + x;
			Tile* tileObj = static_cast<Tile*>(vecTiles[tileIdx]);
			tileObj->SetTileType(TILE_TYPE::EMPTY);
			tileObj->SetTileIdx(0);
		}

		for (PrimCostEdge& edge : edges[nowPos])
		{
			// �̹� �߰��Ǿ� ������ ��ŵ
			if (added[edge._vertex]) continue;
			
			// �ٸ� ��η� �� ���� �ĺ��� �߰ߵǾ��ٸ� ��ŵ
			if (edge._cost > best[edge._vertex]) continue;

			best[edge._vertex] = edge._cost;
			parent[edge._vertex] = nowPos;
			pq.push(edge);
		}
	}
}
