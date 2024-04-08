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
		// ���� GET_MOUSE_POS�� RenderPos���� ��ǥ�̴�.
		// GetMousePos�� KEY�� Update���� ���ŵ� ������ ��ǥ�̴�.
		// �̰��� GetWindowActualPosFromRenderPos�� �־��־� reder��ǥ�� �����쿡 �ش��ϴ� ���� ��ǥ�� �������ش�.
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

	// ��� ������Ʈ�鿡 ���� Init�Լ� ȣ��
	InitObjects();

	// ��� ������Ʈ���� Collider �浹 �� ����
	InitObjectCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::MONSTER);
	InitObjectCollision(OBJECT_TYPE::PROJ_PLAYER, OBJECT_TYPE::MONSTER);

	// ��� �غ� �Ϸ� �Ǿ����Ƿ� ��� ������Ʈ�鿡 ���� Begin�Լ� ȣ��
	// ���� ������ �ִ� ��� ������Ʈ�鿡 ���� Beginȣ��
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

	// EVENT���� ����
	DeleteAllObjects();
}
