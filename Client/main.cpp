// Client.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Client.h"

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
POINT objectScale = {100, 100};

// _In_ : SAL 주석언어
int APIENTRY wWinMain
(
_In_ HINSTANCE hInstance /*실행된 프로세스의 시작 주소*/,
_In_opt_ HINSTANCE hPrevInstance,
_In_ LPWSTR    lpCmdLine,
_In_ int       nCmdShow)
{
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);

    // window 정보 등록
    MyRegisterClass(hInstance);

    // 윈도우 생성
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 단축키 테이블 정보 로딩
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    // Main message loop:
    // GetMessage : 메시지큐에서 메세지 확인할 때까지 대기
    // msg.message == WM_QUIT => return false
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
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
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, winHeight, winWidth, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    // 무효화 영역이 발생한 경우 발생
    // Invalidate 영역
    case WM_PAINT:
        {
            PAINTSTRUCT ps;

            // dc - id반환
            // dc의 목적지는 hWnd
            HDC hdc = BeginPaint(hWnd, &ps); // device context

            const COLORREF rgbRed = 0x000000FF;

            // 직접 펜을 만들어서 DC에 지급
            HPEN pen = CreatePen(PS_SOLID, 2, rgbRed);

            // 자주 쓰는 오브젝트 -> StockObject (prev 생성)
            HBRUSH brush = CreateSolidBrush(0x00FF0000);

            // 기본 pen id값을 받아 둠
            HPEN dpen = (HPEN)SelectObject(hdc, pen);
            HBRUSH dbrush = (HBRUSH)SelectObject(hdc, brush);

            // 변경된 펜으로 사각형을 그림
            Rectangle(hdc,
                objectPos.x - objectScale.x / 2, 
                objectPos.y - objectScale.y / 2, 
                objectPos.x + objectScale.x / 2,
                objectPos.y + objectScale.y / 2);

            // dc의 펜을 원래 펜으로 되돌림 (브러쉬 또한)
            SelectObject(hdc, dpen);
            SelectObject(hdc, dbrush);

            // 다쓴 red pen 삭제
            DeleteObject(pen);

            // end
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
            case 'W':
            {
                objectPos.y -= 5;

                // 마지막 인자 false일경우 clear하지 않는다.
                // InvalidateRect(hWnd, nullptr, false);
                InvalidateRect(hWnd, nullptr, true);
            }
            break;
            case 'S':
            {
                objectPos.y += 5;
                InvalidateRect(hWnd, nullptr, true);
            }
            break;
            case 'A':
            {
                objectPos.x -= 5;
                InvalidateRect(hWnd, nullptr, true);
            }
            break;
            case 'D':
            {
                objectPos.x += 5;
                InvalidateRect(hWnd, nullptr, true);
            }
            break;
            default:
                break;
        }
    }
    case WM_LBUTTONDOWN:
    {
        auto pos = lParam;

        // 비트 연산으로 밀어버림
        g_x = LOWORD(pos); // x
        g_y = HIWORD(pos); // y
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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
