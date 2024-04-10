// Client.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Client.h"
#include "pch.h"
#include <crtdbg.h>
#include "Tool.h"


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int g_x;
int g_y;
int winHeight = 500;
int winWidth = 500;
POINT objectPos = { winHeight / 2, winWidth / 2 };
POINT objectScale = { 100, 100 };
HWND g_hWnd;

class Core;

// _In_ : SAL �ּ����
int APIENTRY wWinMain
(
_In_ HINSTANCE hInstance /*����� ���μ����� ���� �ּ�*/,
_In_opt_ HINSTANCE hPrevInstance,
_In_ LPWSTR    lpCmdLine,
_In_ int       nCmdShow)
{
    // mem leak check
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // _CrtSetBreakAlloc(215);

    
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);

    // window ���� ���
    MyRegisterClass(hInstance);

    // ������ ����
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // Core Init
    if (FAILED(GET_SINGLE(Core)->Init(g_hWnd, POINT{ 800, 800 })))
    {
        MessageBox(nullptr, L"Core intialize Fail", L"ERROR", MB_OK);
        return FALSE;
    }

    // ����Ű ���̺� ���� �ε�
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    // Main message loop:
    // GetMessage : �޽���ť���� �޼��� Ȯ���� ������ ���
    // msg.message == WM_QUIT => return false
    // GetMessage -> PeekMessage(����) -> �׻� ��ȯ�Ѵ�.
    while (1)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message) break;
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            GET_SINGLE(Core)->Progress();
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);

    // �޴��� ����
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, winHeight, winWidth, nullptr, nullptr, hInstance, nullptr);

   g_hWnd = hWnd;

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


// forward declarations...
// ToolScene�� �Լ� ���漱�� �����.
// ��ũ �ܰ迡�� ���δ�.
// INT_PTR CALLBACK TileCountPrc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case ID_SET_TILE:
            {
                INT_PTR ret = DialogBox(hInst, MAKEINTRESOURCE(IDD_TILE_COUNT), hWnd, TileCountPrc);
                if (ret == IDOK)
                {
                    
                }
            }
            break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
 
    // ��ȿȭ ������ �߻��� ��� �߻�
    // Invalidate ����
    case WM_PAINT:
        {
            PAINTSTRUCT ps;

            // dc - id��ȯ
            // dc�� �������� hWnd
            HDC hdc = BeginPaint(hWnd, &ps); // device context

            // Rectangle(hdc, 0, 0, 600, 600);

            EndPaint(hWnd, &ps);
        }
        break;
        // ���콺 �� ó��
        //case WM_MOUSEWHEEL:
        //{
        //    wchar_t buffer[255] = {};
        //    if ((SHORT)HIWORD(wParam) > 0) //���콺���� �ø� ���
        //    {
        //        swprintf_s(buffer, L"WHEEL : %hd", (int16)(HIWORD(wParam)));
        //        SetWindowText(GET_WINDOW_HANDLE, buffer);

        //        KEY->UpdateMouseWheel((int16)(HIWORD(wParam)));
        //    }
        //    else if ((SHORT)HIWORD(wParam) < 0)  //���콺���� ���� ���
        //    {
        //        swprintf_s(buffer, L"WHEEL : %hd", (int16)(HIWORD(wParam)));
        //        SetWindowText(GET_WINDOW_HANDLE, buffer);

        //        KEY->UpdateMouseWheel((int16)(HIWORD(wParam)));
        //    }
        //    else
        //    {
        //    }
        //}
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
