#include "pch.h"
#include "StartScene.h"
#include "Monster.h"
#include "Tile.h"
#include "AI.h"
#include "State_Idle.h"
#include "State_Trace.h"

StartScene::StartScene()
{

}

StartScene::~StartScene()
{

}

void StartScene::InitScene()
{
	_vecGameInfoTexts.resize(uint32(GAME_INFO::END), L"");
}

void StartScene::Update()
{
	Scene::Update();
	UpdateSceneKeyInput();
	UpdateTextOfGameInfo();
}

void StartScene::Render()
{
	Scene::Render();
	RenderTextOfGameInfo();
}

void StartScene::BeginScene()
{
	_vecGameInfoTexts.resize(uint32(GAME_INFO::END), L"");

	auto res = GET_RESOLUTION;

	// Create Player
	Player* player = static_cast<Player*>(CreatePlayer());
	player->SetScale(Vec2(50.f, 50.f));

	// Create Monster
	{
		Monster* monster = static_cast<Monster*>(CreateAndAppendToScene<Monster>(OBJECT_TYPE::MONSTER));
		monster->SetObjectName(L"Mosnter_01");
		monster->SetPos(Vec2(player->GetPos().x, player->GetPos().y - 200.f));

		AI* ai = new AI();
		ai->AddState(new State_Idle());
		ai->AddState(new State_Trace());
		monster->SetModuleAI(new AI());
	}

	// 스폰된 오브젝트들 Init 작업
	InitObjects();

	// Call Objects Begin
	for (int i = 0; i < (uint32)OBJECT_TYPE::END; ++i)
	{
		for (Object* obj : _sceneObjects[i])
		{
			if (obj)
			{
				obj->Begin();
			}
		}
	}
}

void StartScene::EndScene()
{
	for (int i = 0; i < (uint32)OBJECT_TYPE::END; ++i)
	{
		for (Object* obj : _sceneObjects[i])
		{
			if (obj)
			{
				obj->End();
			}
		}
	}

	COLLISION->ResetObjectCollision();
	ResetSceneInfo();
	DeleteAllObjects();
}

void StartScene::UpdateSceneKeyInput()
{
	if (KEY_PRESSED(KEYES::LBTN))
	{
		CheckTileIdx();
	}

	if (KEY_PRESSED(KEYES::DOWN))
	{
		ChnageScene_EV(SCENE_TYPE::TOOL);
	}
}
