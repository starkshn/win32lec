#include "pch.h"
#include "ToolScene.h"
#include "Tile.h"
#include "Texture.h"
#include "TimeManager.h"
#include "PanelUI.h"
#include "ButtonUI.h"
#include "Monster.h"
#include "Button_CloseUI.h"

void SaveTileData(DWORD_PTR, DWORD_PTR)
{
	WCHAR filePath[256] = {};

	// 기억 ㄴㄴ
	OPENFILENAME ofn = {};
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GET_WINDOW_HANDLE;
	ofn.lpstrFile = filePath;
	ofn.nMaxFile = sizeof(filePath);

	// ALL에 대응하는 모든 이름과 모든 확장자가가 와도된다.
	// ofn.lpstrFilter = L"ALL\0*.*";
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0; // ALL\0*.* 으로 지정
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;
	
	wstring contentPath = PATH->GetContentDirPath();
	contentPath += L"tile";
	ofn.lpstrInitialDir = (contentPath).c_str();
	
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
	// Modal
	// 특징 : 해당 창이 모든 포커싱 가진다.
	if (GetSaveFileName(&ofn))
	{
		ToolScene::SaveTileAbsolutPath(filePath);
	}
}

void LoadTileData(DWORD_PTR, DWORD_PTR)
{
	WCHAR filePath[256] = {};

	// 기억 ㄴㄴ
	OPENFILENAME ofn = {};
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GET_WINDOW_HANDLE;
	ofn.lpstrFile = filePath;
	ofn.nMaxFile = sizeof(filePath);

	// ALL에 대응하는 모든 이름과 모든 확장자가가 와도된다.
	// ofn.lpstrFilter = L"ALL\0*.*";
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0; // ALL\0*.* 으로 지정
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring contentPath = PATH->GetContentDirPath();
	contentPath += L"tile";
	ofn.lpstrInitialDir = (contentPath).c_str();

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal
	// 특징 : 해당 창이 모든 포커싱 가진다
	if (GetOpenFileName(&ofn))
	{
		// PathManager의 절대 경로로 부터 상대 경로를 얻는 함수를 통해서
		// LoadTile을 호출해도되고
		wstring relativePath = PATH->GetRelativePathFromAbsolutePath(filePath);
		ToolScene::LoadTileRelativePath(relativePath);

		// 아래 절대 경로를 넣어서 한번에 LoadTile하는 함수를 호출해도 된다.
		// ToolScene::LoadTileAbsolutePath(filePath);
	}
}

ToolScene::ToolScene()
{

}

ToolScene::~ToolScene()
{

}

void ToolScene::InitScene()
{
	_resolution = GET_RESOLUTION;
	_vecGameInfoTexts.resize(uint32(GAME_INFO::END), L"");
}

void ToolScene::Update()
{
	Scene::Update();
	UpdateTextOfGameInfo();
	ChangeTileIndex();

	if (KEY_PRESSED(KEYES::O))
	{
		UI_MANAGER->SetForceFocusingUI(_temp);
	}

	if (KEY_PRESSED(KEYES::ESC))
	{
		if (_toolUI->GetVisible() == false)
		{
			_toolUI->SetVisible(true);
			UI_MANAGER->SetForceFocusingUI(_toolUI);
		}
		else
		{
			_toolUI->SetVisible(false);
			UI_MANAGER->SetForceFocusingUI(nullptr);
		}
	}
}

void ToolScene::Render()
{
	Scene::Render();

	RenderTextOfSceneInfo();
	RenderTextOfGameInfo();
}

// TEMP
void ChangScene(DWORD_PTR, DWORD_PTR)
{
	ChnageScene_EV(SCENE_TYPE::START);
}

void ToolScene::BeginScene()
{
	// Set Camera
	Vec2 res = GET_RESOLUTION;
	CAMERA->SetCameraCurrentLookAtPos(Vec2(res.x / 2.f, res.y / 2.f));

	// Create Player
	Player* player = static_cast<Player*>(CreatePlayer());
	player->SetScale(Vec2(50.f, 50.f));
	
	// Create Monster
	Object* monster = CreateAndAppendToScene<Monster>(OBJECT_TYPE::MONSTER);
	monster->SetPos(Vec2(player->GetPos().x, player->GetPos().y - 200.f));
	
	// =============================================
	// UI
	// =============================================
	// 패널 UI
	UI* outer_PanelUI = static_cast<UI*>(CreateAndAppendToScene<PanelUI>(OBJECT_TYPE::UI));
	outer_PanelUI->SetObjectName(L"Origin_PanelUI");
	outer_PanelUI->SetScale(Vec2(500.f, 300.f));
	outer_PanelUI->SetPos(Vec2(0.f, 300.f));
	outer_PanelUI->SetUIOffSet(Vec2(0.f, 0.f));

	// 버튼 UI
	ButtonUI* inner_ButtonUI = static_cast<ButtonUI*>(CreateAndAppendToScene<ButtonUI>(OBJECT_TYPE::UI));
	inner_ButtonUI->SetScale(Vec2(100.f, 100.f));
	inner_ButtonUI->SetUIOffSet(Vec2(0.f, 0.f));
	inner_ButtonUI->SetObjectName(L"Origin_Test_ButtonUI");
	inner_ButtonUI->SetClickFunc(ChangScene, 0, 0); // call back 임시구현

	// Close BTN UI
	ButtonUI* closeButtonUI = static_cast<ButtonUI*>(CreateAndAppendToScene<Button_CloseUI>(OBJECT_TYPE::UI));
	closeButtonUI->SetObjectName(L"Origin_CancleBTN");
	closeButtonUI->SetScale(Vec2(30.f, 30.f));
	closeButtonUI->SetPos(outer_PanelUI->GetPos());
	closeButtonUI->SetUIOffSet(Vec2(outer_PanelUI->GetScale().x - 30.f, 0.f));
	closeButtonUI->SetTexture(RESOURCE->GetTexture(L"CloseUI", L"CloseUI.bmp"));
	closeButtonUI->SetClickFunc(closeButtonUI, static_cast<OBJECT_MEM_FUNC>(&Button_CloseUI::CloseThisUI)); // 호출할 함수 바인딩
	
	// Inner Class 등록
	outer_PanelUI->SetInnerUI(inner_ButtonUI);
	outer_PanelUI->SetInnerUI(closeButtonUI);

	// Deep Copy Contstructor Test
	UI* ClonePanel = outer_PanelUI->Clone();
	ClonePanel->SetPos(outer_PanelUI->GetPos() + Vec2(700.f, 0.f));

	_temp = ClonePanel;

	// ESC 누르면 발생하는 Tool UI
	_toolUI = static_cast<UI*>(CreateAndAppendToScene<PanelUI>(OBJECT_TYPE::UI));
	_toolUI->SetObjectName(L"ToolUIPanel");
	_toolUI->SetScale(Vec2(300.f, 700.f));
	_toolUI->SetPos(Vec2(res.x - _toolUI->GetScale().x, 0.f));
	_toolUI->SetUIOffSet(Vec2(0.f, 0.f));
	static_cast<PanelUI*>(_toolUI)->SetCanDrag(false);
	
	// toolUI의 저장 버튼 UI
	ButtonUI* toolUI_SaveButton = static_cast<ButtonUI*>(CreateAndAppendToScene<ButtonUI>(OBJECT_TYPE::UI));
	toolUI_SaveButton->SetScale(Vec2(100.f, 50.f));
	toolUI_SaveButton->SetUIOffSet(Vec2(50.f, 50.f));
	toolUI_SaveButton->SetObjectName(L"toolUI_SaveButton");
	toolUI_SaveButton->SetClickFunc(&SaveTileData, 0, 0); // 호출할 함수 바인딩
	toolUI_SaveButton->SetButtonText(L"SaveTile");

	// toolUI의 로드 버튼 UI
	ButtonUI* toolUI_LoadButton = static_cast<ButtonUI*>(CreateAndAppendToScene<ButtonUI>(OBJECT_TYPE::UI));
	toolUI_LoadButton->SetScale(Vec2(100.f, 50.f));
	toolUI_LoadButton->SetUIOffSet(Vec2(175.f, 50.f));
	toolUI_LoadButton->SetObjectName(L"toolUI_LoadButton");
	toolUI_LoadButton->SetClickFunc(&LoadTileData, 0, 0); // 호출할 함수 바인딩
	toolUI_LoadButton->SetButtonText(L"LoadTile");

	// InnerClass들 등록
	_toolUI->SetInnerUI(toolUI_SaveButton);
	_toolUI->SetInnerUI(toolUI_LoadButton);
	_toolUI->SetVisible(false);

	// TODO
	 // toolUI의 로드 버튼 UI
	_testBTN = static_cast<UI*>(CreateAndAppendToScene<ButtonUI>(OBJECT_TYPE::UI));
	_testBTN->SetScale(Vec2(100.f, 100.f));
	_testBTN->SetPos(Vec2(res.x - _testBTN->GetScale().x, 0.f));
	_testBTN->SetUIOffSet(Vec2(0.f, 0.f));
	_testBTN->SetObjectName(L"testBTN");

	// 아래 멤버 함수를 바인딩하는 경우 
	// 특정 클래스 캐스팅(네임스페이스::멤버함수) 이런식으로 전달해주어야 한다.
	static_cast<ButtonUI*>(_testBTN)->SetClickFunc(this, static_cast<SCENE_MEM_FUNC>(&ToolScene::Test)); // 호출할 함수 바인딩
	static_cast<ButtonUI*>(_testBTN)->SetButtonText(L"testBTN");

	// 스폰된 오브젝트들 Init 작업
	InitObjects();
}

void ToolScene::EndScene()
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

	DeleteAllObjects();
}

void ToolScene::UpdateTextOfGameInfo()
{
	_vecGameInfoTexts[uint32(GAME_INFO::GAMEINFO_FPS)] = L"FPS : " + to_wstring(FPS);
	_vecGameInfoTexts[uint32(GAME_INFO::GAMEINFO_DT)] = L"DeltaTime : " + to_wstring(DT_F);

	uint32 objCount = GetSceneAllObjectCount();
	_vecGameInfoTexts[uint32(GAME_INFO::GAMEINFO_OBJECT_COUNT)] = L"Objet Count : " + to_wstring(objCount);

	Object* curObject = GetCurMouseHoverObject();
	wstring curObjectName = L"None";
	if (nullptr != curObject)
	{
		if (curObject->GetMouseHoverOnThisObject())
		{
			curObjectName = curObject->GetObjectName();
		}
	}

	_vecGameInfoTexts[uint32(GAME_INFO::GAMEINFO_CUR_OBJECT)] = L"Objet Name : " + curObjectName;
}

void ToolScene::RenderTextOfGameInfo()
{
	for (uint32 i = 0; i < uint32(GAME_INFO::END); ++i)
	{
		if (_vecGameInfoTexts[i] != L"")
		{
			TextOut(GET_MEMDC, 10, int32(50.f + i * 20.f), _vecGameInfoTexts[i].c_str(), int32(_vecGameInfoTexts[i].length()));
		}
	}
}

void ToolScene::RenderTextOfSceneInfo()
{
	wstring toolUI = L"ESC : ToolUI";
	TextOut(GET_MEMDC, 10, 10, toolUI.c_str(), int32(toolUI.length()));

	wstring btnUI = L"Click BTN : Goto START SCENE";
	TextOut(GET_MEMDC, 10, 30, btnUI.c_str(), int32(btnUI.length()));
}

void ToolScene::ChangeTileIndex()
{
	if (KEY_PRESSED(KEYES::LBTN))
	{
		// 현재 윈도우 렌더링 마우스 좌표
		Vec2 renderMousePos = RENDER_MOUSE_POS;

		// 현재 윈도우 실제 마우스 좌표 (절대 좌표)
		Vec2 windowMousePos = WINDOW_MOUSE_POS;
		
		// 현재 씬 타일 X Y 개수 반환
		Vec2 tileXYCount	= GetCurrentTileXYCount();
		int32 tileXCount	= (int32)tileXYCount.x;
		int32 tileYCount	= (int32)tileXYCount.y;

		int32 tileColIdx = int32(windowMousePos.x / TILE_SIZE);
		int32 tileRowIdx = int32(windowMousePos.y / TILE_SIZE);

		// index range check
		if ((tileColIdx >= tileXCount) || (tileRowIdx >= tileYCount)) return;

		uint32 tileObjectIdx = (tileRowIdx * tileXCount) + tileColIdx;
		Tile* tileObj = static_cast<Tile*>(GetObjectByTypeAndIndex(OBJECT_TYPE::DEFAULT_TILE, tileObjectIdx));
		if (nullptr == tileObj)
		{
			assert(0);
			return;
		}

		Vec2 tileRenderPos = tileObj->GetRenderPos();
		int32 maxX = int32(tileRenderPos.x + tileObj->GetScale().x);
		int32 maxY = int32(tileRenderPos.y + tileObj->GetScale().y);
		
		// 마우스의 render 좌표와 타일 render 좌표가 일치하는지 확인
		if ((renderMousePos.x <= maxX && renderMousePos.x >= tileRenderPos.x) && (renderMousePos.y <= maxY && renderMousePos.y >= tileRenderPos.y))
		{
			// 더이상 타일을 증가 시킬 수 없는 경우 처음으로 되돌림
			if (tileObj->GetTileIdx() + 1 >= MAX_TILE_COUNT)
			{
				tileObj->SetTileIdx(0);
			}
			// 증가 시킬 수 있는 경우
			else
			{
				tileObj->SetTileIdx(tileObj->GetTileIdx() + 1);
			}
		}
	}
}


void ToolScene::SaveTileRelativePath(const wstring& relativePath)
{
	wstring absolutePath = PATH->GetContentDirPath();
	wstring allPath = absolutePath + relativePath;

	FILE* file = nullptr; // keunal object
	_wfopen_s(&file, allPath.c_str(), L"wb");
	assert(file);

	Scene* curScene = SCENE->GetCurrentScene();

	// 데이터 저장
	Vec2 xyCounts = curScene->GetCurrentTileXYCount();
	uint32 countX = uint32(xyCounts.x);
	uint32 countY = uint32(xyCounts.y);
	
	// 타일 가로 세로 개수 저장
	fwrite(&countX, sizeof(uint32), 1, file);
	fwrite(&countY, sizeof(uint32), 1, file);

	// 각각의 타일들에 대해서 가로 세로 개수 저장
	const vector<Object*>& vecTiles = curScene->GetObjectsByType(OBJECT_TYPE::DEFAULT_TILE);
	for (uint32 i = 0; i < vecTiles.size(); ++i)
	{
		static_cast<Tile*>(vecTiles[i])->Save(file);
	}

	// stream close
	fclose(file);
}

void ToolScene::SaveTileAbsolutPath(const wstring& absolutePath)
{
	FILE* file = nullptr; // keunal object
	_wfopen_s(&file, absolutePath.c_str(), L"wb");
	assert(file);

	Scene* curScene = SCENE->GetCurrentScene();

	// 데이터 저장
	Vec2 xyCounts = curScene->GetCurrentTileXYCount();
	uint32 countX = uint32(xyCounts.x);
	uint32 countY = uint32(xyCounts.y);

	// 타일 가로 세로 개수 저장
	fwrite(&countX, sizeof(uint32), 1, file);
	fwrite(&countY, sizeof(uint32), 1, file);

	// 각각의 타일들에 대해서 가로 세로 개수 저장
	const vector<Object*>& vecTiles = curScene->GetObjectsByType(OBJECT_TYPE::DEFAULT_TILE);
	for (uint32 i = 0; i < vecTiles.size(); ++i)
	{
		static_cast<Tile*>(vecTiles[i])->Save(file);
	}

	// stream close
	fclose(file);
}

void ToolScene::LoadTileRelativePath(const wstring& relativePath)
{
	wstring absolutePath = PATH->GetContentDirPath();
	wstring allPath = absolutePath + relativePath;

	FILE* file = nullptr; // keunal object
	_wfopen_s(&file, allPath.c_str(), L"rb");
	assert(file);

	// 데이터 저장
	uint32 countX = 0;
	uint32 countY = 0;

	fread(&countX, sizeof(uint32), 1, file);
	fread(&countY, sizeof(uint32), 1, file);

	Scene* curScene = SCENE->GetCurrentScene();
	curScene->CreateTile(countX, countY);
	const vector<Object*>& vecTiles = curScene->GetObjectsByType(OBJECT_TYPE::DEFAULT_TILE);

	for (uint32 i = 0; i < vecTiles.size(); ++i)
	{
		static_cast<Tile*>(vecTiles[i])->Load(file);
	}

	// stream close
	fclose(file);
}

void ToolScene::LoadTileAbsolutePath(const wstring& absolutePath)
{
	FILE* file = nullptr; // keunal object
	_wfopen_s(&file, absolutePath.c_str(), L"rb");
	assert(file);

	// 데이터 저장
	uint32 countX = 0;
	uint32 countY = 0;

	fread(&countX, sizeof(uint32), 1, file);
	fread(&countY, sizeof(uint32), 1, file);

	Scene* curScene = SCENE->GetCurrentScene();
	curScene->CreateTile(countX, countY);
	const vector<Object*>& vecTiles = curScene->GetObjectsByType(OBJECT_TYPE::DEFAULT_TILE);

	for (uint32 i = 0; i < vecTiles.size(); ++i)
	{
		static_cast<Tile*>(vecTiles[i])->Load(file);
	}

	// stream close
	fclose(file);
}

