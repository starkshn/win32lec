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

	// 현재 씬에 타일 생성 및 미로 맵 생성
	_curScene->CreateTile(11, 11);
	SetCurSceneBoardXYCounts(Vec2(11.f, 11.f));

	// 랜덤 미로맵 생성
	GenerateBoard_Prim();
	// GenerateBoard_Kruskal();

	// 타일의 1, 1 위치 좌표 구하고 플레이어 위치시키기
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

	// 현재 씬 타일 X Y 개수 가져오기
	Vec2 counts = _curScene->GetCurrentTileXYCount();
	const int32 countX = int32(counts.x);
	const int32 countY = int32(counts.y);

	// N * N 격자를 만들고 벽 두르기 
	{
		// 2로 나누어 떨어지면 WALL로 셋팅
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

	// 랜덤한 가중치를 간선마다 추가하고 이를 pq에 넣음
	{
		// 2로 나누어 떨어지지 않는 지점에 랜덤한 가중치 설정
		for (int32 y = 0; y < countY; ++y)
		{
			for (int32 x = 0; x < countX; ++x)
			{
				if (x % 2 == 0 || y % 2 == 0)
					continue;

				// 우측을 연결하는 간선 후보를 만든다.
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
	

	// 유니온 파인드 (Disjoint Set 객체 생성)
	DisjointSet sets(countY * countX);

	// 크루스칼 수행
	{
		// pq가 빌때까지 아래의 과정을 반복한다.
		while (!pq.empty())
		{
			CostEdge now = pq.top(); pq.pop();
			int32 u = int32(now.u.y * countY) + int32(now.u.x);
			int32 v = int32(now.v.y * countY) + int32(now.v.x);

			// 같은 그룹인지 아닌지 확인
			if (sets.FindParent(u) == sets.FindParent(v)) continue;

			// 같은 그룹이 아니라면 합친다.
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

	// 현재 씬 타일 X Y 개수 가져오기
	Vec2 counts = _curScene->GetCurrentTileXYCount();
	const int32 countX = int32(counts.x);
	const int32 countY = int32(counts.y);

	// N * N 격자를 만들고 벽 두르기 
	{
		// 2로 나누어 떨어지면 WALL로 셋팅
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

	// 랜덤한 가중치 설정
	{
		// edges 후보의 간선 비용을 랜덤 비용으로 설정한다.
		for (int32 y = 0; y < countY; ++y)
		{
			for (int32 x = 0; x < countX; ++x)
			{
				// WALL에는 관심 없고 초록 점을 기준으로 오른, 아래 뚫.
				if (x % 2 == 0 || y % 2 == 0)
					continue;

				// 우측을 연결하는 간선 후보를 만든다.
				if (x < countX - 2)
				{
					// [s] [벽] [d] [벽]
					const int32 randVal = ::rand() % 100;
					Vec2 u = Vec2{ float(x), float(y)};
					Vec2 v = Vec2{ float(x + 2), float(y) };
					edges[u].push_back(PrimCostEdge{ randVal, v });
					edges[v].push_back(PrimCostEdge{ randVal, u });
				}

				// 아래로 연결하는 간선 후보 만들기
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

	// 탐색할 정점이 트리에 포함되어 있는지 확인할 map
	map<Vec2, bool> added;

	// 추적하기 위한 용도의 map
	map<Vec2, Vec2> parent;

	// 최소 간선 정보를 담을 map
	map<Vec2, int32> best;

	// 초기화 작업
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
		
		// 맵에 적용
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
			// 이미 추가되어 있으면 스킵
			if (added[edge._vertex]) continue;
			
			// 다른 경로로 더 좋은 후보가 발견되었다면 스킵
			if (edge._cost > best[edge._vertex]) continue;

			best[edge._vertex] = edge._cost;
			parent[edge._vertex] = nowPos;
			pq.push(edge);
		}
	}
}
