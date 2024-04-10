#include "Tool.h"
#include "resource.h"
#include "Types.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ToolScene.h"
#include "EventManager.h"
#include "Func.h"

INT_PTR TileCountPrc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDOK)
		{
			uint32 maxRow = uint32(GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false));
			uint32 maxCol = uint32(GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false));
			
			// 현재 씬 가져오기
			Scene* curScene = SceneManager::GetInstance()->GetCurrentScene();
			ToolScene* toolScene = dynamic_cast<ToolScene*>(curScene);

			if (nullptr == toolScene)
			{
				assert(nullptr);
				return (INT_PTR)TRUE;
			}

			// Tile 삭제
			toolScene->DeleteAllObjectsByType(OBJECT_TYPE::DEFAULT_TILE);

			// Tile 생성
			toolScene->CreateTile(maxCol, maxRow);
			toolScene->SetCurrentTileXYCount(Vec2(maxCol, maxRow));

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
	}
	break;
	default:
		break;
	}

	return (INT_PTR)FALSE;
}
