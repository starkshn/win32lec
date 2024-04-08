#include "pch.h"
#include "MainMenuScene.h"
#include "Object.h"
#include "Player.h"
#include "Rect.h"
#include "Brick.h"
#include "Monster.h"
#include "Texture.h"

MainMenuScene::MainMenuScene()
{

}

MainMenuScene::~MainMenuScene()
{

}

void MainMenuScene::InitScene()
{
	
}

void MainMenuScene::Update()
{
	Scene::Update();

	/*if (KEY_PRESSED(KEYES::DOWN))
	{
		ChnageScene_EV(SCENE_TYPE::START);
	}*/

	if (KEY_PRESSED(KEYES::LBTN))
	{
		// 현재 GET_MOUSE_POS는 RenderPos기준 좌표이다.
		// GetMousePos는 KEY의 Update에서 갱신된 렌더링 좌표이다.
		// 이값을 GetWindowActualPosFromRenderPos에 넣어주어 reder좌표를 윈도우에 해당하는 실제 좌표로 변경해준다.
		Vec2 winActualPos = CAMERA->GetWindowActualPosFromRenderPos(GET_MOUSE_POS);
		CAMERA->SetDestLookAtPos(winActualPos);
	}
}

void MainMenuScene::Render()
{
	Scene::Render();
}

void MainMenuScene::BeginScene()
{
	auto res = GET_RESOLUTION;

	// Create Player
	CreatePlayer();

	// Create Monster
	CreateAndAppendToScene<Monster>(OBJECT_TYPE::MONSTER);

	// 모든 오브젝트들에 대해 Init함수 호출
	InitObjects();

	// 모든 오브젝트들의 Collider 충돌 값 셋팅
	InitObjectCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::MONSTER);
	InitObjectCollision(OBJECT_TYPE::PROJ_PLAYER, OBJECT_TYPE::MONSTER);

	// 모든 준비가 완료 되었으므로 모든 오브젝트들에 대해 Begin함수 호출
	// 씬이 가지고 있는 모든 오브젝트들에 대해 Begin호출
	ObjectBegin();
}

void MainMenuScene::EndScene()
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

	// EVENT에게 전달
	DeleteAllObjects();
}
