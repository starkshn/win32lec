#pragma once
#include <Windows.h>


// ===========================
// TILE COUNT WINDOW PROC
// ==========================
INT_PTR CALLBACK TileCountPrc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

// 윈도우 처리기 함수를 만들고 싶으면 __stdcall 반환 타입 다음에 붙여야 된다.
// 함수 호출 규약
// CALLBACK은 표준 함수 호출 규약을 메크로 걸어 놓음