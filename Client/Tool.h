#pragma once
#include <Windows.h>


// ===========================
// TILE COUNT WINDOW PROC
// ==========================
INT_PTR CALLBACK TileCountPrc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

// ������ ó���� �Լ��� ����� ������ __stdcall ��ȯ Ÿ�� ������ �ٿ��� �ȴ�.
// �Լ� ȣ�� �Ծ�
// CALLBACK�� ǥ�� �Լ� ȣ�� �Ծ��� ��ũ�� �ɾ� ����