#include "pch.h"
#include "Player.h"
#include "Projectile.h"
#include "Projectile_Sin.h"
#include "Projectile_Cos.h"
#include "Texture.h"
#include "Collider.h"
#include "Component.h"
#include "Animator.h"
#include "Animation.h"
#include "Tile.h"
#include "structs.h"

Player::Player()
{

}

Player::~Player()
{

}

Player* Player::Clone()
{
	return new Player(*this);
}

void Player::Update()
{
	UnitObject::Update();

	_accTime += DT_F;

	if (GetOuterSceneType() != SCENE_TYPE::TOOL)
	{
		if (KEY_PRESSED(KEYES::LBTN))
		{
			AStar();
		}
	}

	if (_accTime >= 0.5f)
	{
		if (_pathIdx >= _pathTileID.size())
		{
			return;
		}

		int32 tileIdx = _pathTileID[_pathIdx++];
		Tile* tile = static_cast<Tile*>(SCENE->GetCurrentScene()->GetObjectByTypeAndIndex(OBJECT_TYPE::DEFAULT_TILE, tileIdx));

		Vec2 tilePos = tile->GetPos();
		SetPos(Vec2(tilePos.x + 30.f, tilePos.y + 30.f));
		SetPlayerCurTileID(tile->GetTileID());
		_accTime = 0.f;
	}

	// DisMovement();
}

void Player::Render()
{	
	UnitObject::Render();
}

void Player::Init()
{
	// get resolution
	auto res = GET_RESOLUTION;

	// set name
	SetObjectName(L"Player");

	// Create Collider
	{
		Collider* compCollider = CreateComponent<Collider>(COMP_TYPE::COLLIDER);
		Vec2 playerScale = GetScale();
		compCollider->SetScale(Vec2(float(playerScale.x), float(playerScale.y)));
		compCollider->SetOffset(Vec2(0.f, 0.f));
	}

	// Create Animator
	// - Create Animation
	{
		Animator* compAnimator = CreateComponent<Animator>(COMP_TYPE::ANIMATOR);
		Texture* animRes = static_cast<Texture*>(RESOURCE->LoadTexture(L"PlayerAnim", L"texture\\ZeldaAnimation_Mazenta.bmp"));

		// Create Animation
		compAnimator->CreateAnimation(Z_WALK_FRONT, animRes, Vec2(0.f, 520.f), Vec2(120.f, 130.f), Vec2(120.f, 0), 0.05f, 10);
		Animation* anim = compAnimator->FindAnimation(Z_WALK_FRONT);
		compAnimator->SetCurrentAnim(anim);
		anim->SetAnimLoop(true);

		// Set Animation's Frame
		uint32 _max = anim->GetAnimMaxFrame();
		for (uint32 i = 0; i < _max; ++i)
		{
			AnimFrame& finfo = anim->GetAnimFrame(i);
			finfo._offset = Vec2(0.f, -50.f);
		}
	}
}

void Player::Begin()
{

}

void Player::End()
{

}

void Player::Attack()
{
	Object* proj = new Projectile_Sin();
	CreateObject(proj, OBJECT_TYPE::PROJ_PLAYER);
	proj->Init();
}

void Player::DisMovement()
{
	auto type = SCENE->GetCurrentSceneType();
	switch (type)
	{
	case SCENE_TYPE::MAIN_MENU:
		MoveWASD();
		break;
	case SCENE_TYPE::START:
		break;
	case SCENE_TYPE::STAGE_01:
		break;
	case SCENE_TYPE::STAGE_02:
		break;
	case SCENE_TYPE::TOOL:
		break;
	default:
		break;
	}
}

void Player::MoveWASD()
{
	auto pos = GetPos();

	if (KEY_HOLD(KEYES::W))
	{
		pos.y -= 100.f * DT_F;
	}

	if (KEY_HOLD(KEYES::A))
	{
		pos.x -= 100.f * DT_F;
	}

	if (KEY_HOLD(KEYES::S))
	{
		pos.y += 100.f * DT_F;
	}

	if (KEY_HOLD(KEYES::D))
	{
		pos.x += 100.f * DT_F;
	}

	if (KEY_PRESSED(KEYES::SPACE))
	{
		CreateProjectile();
	}

	SetPos(pos);
}

// TODO
void Player::CreateProjectile()
{
	// None Template
	Object* proj = new Projectile_Sin();
	CreateObject(proj, OBJECT_TYPE::PROJ_PLAYER);

	/*GetOuterScene()->SpawnDynamicObject<Projectile_Cos>
		(
			OBJ_PROJECTILE,
			DEFAULT_OBJECT_STATE,
			DEFAULT_PROJECTILE_POS,
			DEFAULT_PROJ_SCALE,
			DEFAULT_PROJ_SPEED
		);*/


	 proj->Init();
}

void Player::AStar()
{
	// 실제 좌표가 아니라 각각의 타일 마다 ID를 부여하여 구현함
	// 
	// 실제 Scene애서는 아래처럼 타일들을 생성하여 벡터에 담고있음
	// [0] [1] [2] [3] [4] [5] [6] [7] [8]
	// 
	// 아래는 실제 StartScene애서 보여지는 타일들 배치
	// [0] [1] [2] 
	// [3] [4] [5]
	// [6] [7] [8]
	//
	// 때문에 2차원 배열의 행과 열의 값을 통해서 일차원 배열의 인덱스를 구하고
	// 일차원 배열의 인덱스 값을 통해서 2차원 배열의 행과 열을 구하는 로직이 들어감
	// 가령 일차원 배열의 5번 인덱스를 2차원 배열의 행과 열로 나타내고 싶다면
	// 현재 씬의 2차원 배열읠 최대 열의 값을 X라 가정하면
	// 2차원 배열의 행의 값 : 5 / X -> 1
	// 2차원 배열의 열의 값 : 5 % X -> 2
	// Row : 1, Col : 2 -> 1행 2열에 5번 인덱스 타일이 위치하게 됨.
	//
	// 반대로 1행 2열의 5번 인덱스를 다시 일차원으로 놔두는 방법은
	// Row(1) * X(3) + Col(2) => 5
	// 이렇게 일차원으로 변경이 가능함.


	// 현재 플레이어가 서있는 타일의 아이디 가져오기
	if (QueueEmpty()) return;
	int32 curTileID = GetPlayerCurTileID();
	int32 curDestTileID = GetDestTileID(); PopFront();

	// Board X, Y 값 가져오기
	Vec2 boardXYCounts = BOARD->GetCurSceneBoardXYCounts();
	int32 boardXCount = int32(boardXYCounts.x);
	int32 boardYCount = int32(boardXYCounts.y);

	Tile* curTileObj = static_cast<Tile*>(SCENE->GetCurrentScene()->GetObjectByTypeAndIndex(OBJECT_TYPE::DEFAULT_TILE, curTileID));
	NULL_PTR_CHECK(curTileObj);

	// 출발점의 타일 ID와 현재 서있는 타일 ID가 다른경우 assert
	assert(curTileObj->GetTileID() == curTileID);

	// 부모 추적
	static map<int32, int32> parent;
	parent[curTileID] = curTileID;

	// 최적의 값 벡터 초기화
	vector<vector<int32>> best(int32(boardXYCounts.y), vector<int32>(int32(boardXYCounts.x), INT32_MAX));
		
	// PQ
	priority_queue<NodeForAStar, vector<NodeForAStar>, greater<NodeForAStar>> pq;

	// DIR
	DIR_BOARD dir;

	// Cost
	int32 cost[] =
	{
		10, // LEFT
		10, // DOWN
		10, // RIGHT
		10, // UP
		14, // LT
		14, // LD
		14, // RD
		14  // RT
	};
		
	// 현재 서있는 타일 X Y 인덱스 
	int32 curTileXIdx = curTileID % boardXCount;
	int32 curTileYIdx = curTileID / boardXCount;

	// 목표 지점 타일 X, Y 인덱스
	int32 destTileXIdx = curDestTileID % boardXCount;
	int32 destTileYIdx = curDestTileID / boardXCount;

	// 목표지점 타일 ID
	int32 destTileID = (boardXCount * destTileYIdx) + destTileXIdx;
	
	// F = G + H
	// 휴리스틱 값 계산
	int32 h = 10 * (abs(destTileXIdx - curTileXIdx) + abs(destTileYIdx - curTileYIdx));

	// 시작점과 도착점 사이의 거리 비용
	int32 g = 0;

	pq.push(NodeForAStar{g + h, g, curTileID });
	best[curTileYIdx][curTileXIdx] = g + h;
	parent[curTileID] = curTileID;

	while (!pq.empty())
	{
		NodeForAStar now = pq.top(); pq.pop();
		int32 nowID = now.id;
		int32 nowX = now.id % boardXCount; // 열 계산
		int32 nowY = now.id / boardXCount; // 행 계산
		
		// 최적의 값이 아니라면 스킵
		if (best[nowY][nowX] < now.f) continue;
			
		// 최적의 값으로 갱신
		best[nowY][nowX] = now.f;

		// 목표 지점(ID라면)이라면 탈출
		if (nowID == destTileID)
		{
			break;
		}

		for (int32 _dir = 0; _dir < 4; ++_dir)
		{				
			// 방향에 따른 다음 아이디
			int32 nextID = dir.GetDirIdx(_dir, nowID, boardXCount, boardYCount);
			int32 nextXIdx = nextID % boardXCount; // 열 계산
			int32 nextYIdx = nextID / boardXCount; // 행 계산

			// ID를 기반으로 행, 열 구해서 갈 수 있는지 없는지 확인한다
			if (CanGo(nextID, boardXCount, boardYCount))
			{
				Tile* nextTileObj = static_cast<Tile*>(SCENE->GetCurrentScene()->GetObjectByTypeAndIndex(OBJECT_TYPE::DEFAULT_TILE, nextID));
				NULL_PTR_CHECK(nextTileObj);
				TILE_TYPE nextTileType = nextTileObj->GetTileType();

				if (nextTileType == TILE_TYPE::EMPTY)
				{
					// g 값 구하기
					int32 nextG = now.g + cost[_dir];

					// 휴리스틱 계산
					int32 h = 10 * (abs(destTileXIdx - nextXIdx) + abs(destTileYIdx - nextYIdx));

					if (best[nextYIdx][nextXIdx] > nextG + h)
					{
						best[nextYIdx][nextXIdx] = nextG + h;
						pq.push(NodeForAStar{ nextG + h, nextG, nextID });
						parent[nextID] = nowID;
					}
				}
			}
		}
	}
	
	_pathTileID.clear();
	_pathIdx = 0;
	int32 destID = curDestTileID;
	while (true)
	{
		_pathTileID.push_back(destID);

		if (parent[destID] == destID) break;

		destID = parent[destID];
	}

	reverse(_pathTileID.begin(), _pathTileID.end());
}

bool Player::CanGo(int32 id, int32 boardX, int32 boardY)
{
	int32 x = id % boardX;
	int32 y = id / boardX;

	if (x >= 0 && x < boardX && y >= 0 && y < boardY)
	{
		return true;
	}
	return false;
}

