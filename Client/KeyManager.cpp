#include "pch.h"
#include "KeyManager.h"

KeyManager::KeyManager()
{
	VK_Mapping[0] = VK_LEFT;
	VK_Mapping[1] = VK_DOWN;
	VK_Mapping[2] = VK_RIGHT;
	VK_Mapping[3] = VK_UP;
	VK_Mapping[4] = 'Q';
	VK_Mapping[5] = 'E';
	VK_Mapping[6] = 'R';
	VK_Mapping[7] = 'T';
	VK_Mapping[8] = 'Y';
	VK_Mapping[9] = 'U';
	VK_Mapping[10] = 'I';
	VK_Mapping[11] = 'O';
	VK_Mapping[12] = 'P';
	VK_Mapping[13] = 'W';
	VK_Mapping[14] = 'A';
	VK_Mapping[15] = 'S';
	VK_Mapping[16] = 'D';
	VK_Mapping[17] = VK_MENU;
	VK_Mapping[18] = VK_LSHIFT;
	VK_Mapping[19] = VK_CONTROL;
	VK_Mapping[20] = VK_SPACE;
	VK_Mapping[21] = VK_RETURN;
	VK_Mapping[22] = VK_ESCAPE;
}

KeyManager::~KeyManager()
{

}

void KeyManager::Init()
{
	for (int i = 0; i < (int)KEYES::LAST; ++i)
	{
		_keys.push_back(KeyInfo{KEY_STATE::NONE, false});
	}
}

void KeyManager::Update()
{
	// focused window check
	// HWND mainhWnd = GET_WINDOW_HANDLE();
	HWND hWnd = GetFocus();

	if (hWnd != nullptr)
	{
		for (int i = 0; i < (int)KEYES::LAST; ++i)
		{
			// key check
			if (GetAsyncKeyState(VK_Mapping[i]) & 0x8000)
			{
				if (_keys[i]._prevPressedState)
				{
					_keys[i]._keyState = KEY_STATE::HOLD;
				}
				else
				{
					_keys[i]._keyState = KEY_STATE::PRESSED;
				}

				_keys[i]._prevPressedState = true;
			}
			else
			{
				if (_keys[i]._prevPressedState)
				{
					_keys[i]._keyState = KEY_STATE::RELEASED;
				}
				else
				{
					_keys[i]._keyState = KEY_STATE::NONE;
				}

				_keys[i]._prevPressedState = false;
			}
		}

		// 임시로 Scene간 이동을 가능하게 한 코드이다.
		// change scene
		if (GET_KEY_STATE(KEYES::UP) == KEY_STATE::HOLD)
		{
			if (SCENE->GetCurrentSceneType() == SCENE_TYPE::MAIN_MENU) return;
			SCENE->ChangeScene(SCENE_TYPE::MAIN_MENU);
		}
		
		if (GET_KEY_STATE(KEYES::DOWN) == KEY_STATE::HOLD)
		{
			if (SCENE->GetCurrentSceneType() == SCENE_TYPE::START) return;
			SCENE->ChangeScene(SCENE_TYPE::START);
		}
	}
	else
	{
		for (int i = 0; i < (int)KEYES::LAST; ++i)
		{
			_keys[i]._prevPressedState = false;

			if (_keys[i]._keyState == KEY_STATE::PRESSED || _keys[i]._keyState == KEY_STATE::HOLD)
			{
				_keys[i]._keyState = KEY_STATE::RELEASED;
			}
			else if (_keys[i]._keyState == KEY_STATE::RELEASED)
			{
				_keys[i]._keyState = KEY_STATE::NONE;
			}
		}
	}
}