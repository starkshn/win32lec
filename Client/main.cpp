// Client.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Client.h"
#include <vector>
using std::vector;

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

struct ObjectInfo
{
    POINT _objPos;
    POINT _objScale;
};

vector<ObjectInfo> objects;


int g_x;
int g_y;
int winHeight = 500;
int winWidth = 500;
POINT objectPos = { winHeight / 2, winWidth / 2 };
POINT objectScale = { 100, 100 };
HWND g_hWnd;

// _In_ : SAL �ּ����
int APIENTRY wWinMain
(
_In_ HINSTANCE hInstance /*����� ���μ����� ���� �ּ�*/,
_In_opt_ HINSTANCE hPrevInstance,
_In_ LPWSTR    lpCmdLine,
_In_ int       nCmdShow)
{
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

    // ����Ű ���̺� ���� �ε�
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    DWORD prevCount = GetTickCount();

    // Main message loop:
    // GetMessage : �޽���ť���� �޼��� Ȯ���� ������ ���
    // msg.message == WM_QUIT => return false
    // GetMessage -> PeekMessage(����) -> �׻� ��ȯ�Ѵ�.

    DWORD accCount = GetTickCount();

    while (1)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            DWORD time = GetTickCount();
            if (WM_QUIT == msg.message) break;
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            accCount += GetTickCount() - time;
        }
        else
        {
            DWORD curCount = GetTickCount();
            if (curCount - prevCount > 1000)
            {
                float ratio = (float)accCount / 1000.f;
                wchar_t buffer[50] = {};
                swprintf_s(buffer, L"Ratio : %f", ratio);
                SetWindowText(g_hWnd, buffer);
            }

            prevCount = curCount;
            accCount = 0;

            // game code ����
            // design pattern
            
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

   g_hWnd = hWnd;

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

POINT leftTop;
POINT rightBottom;
bool trigger = false;

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
    // ��ȿȭ ������ �߻��� ��� �߻�
    // Invalidate ����
    case WM_PAINT:
        {
            PAINTSTRUCT ps;

            // dc - id��ȯ
            // dc�� �������� hWnd
            HDC hdc = BeginPaint(hWnd, &ps); // device context

            const COLORREF rgbRed = 0x000000FF;

            // ���� ���� ���� DC�� ����
            HPEN pen = CreatePen(PS_SOLID, 2, rgbRed);

            // ���� ���� ������Ʈ -> StockObject (prev ����)
            HBRUSH brush = CreateSolidBrush(0x00FF0000);

            // �⺻ pen id���� �޾� ��
            HPEN dpen = (HPEN)SelectObject(hdc, pen);
            HBRUSH dbrush = (HBRUSH)SelectObject(hdc, brush);

            if (trigger)
            {
                // ����� ������ �簢���� �׸�
                Rectangle(hdc,
                    leftTop.x,
                    leftTop.y,
                    rightBottom.x,
                    rightBottom.y);
            }

            for (auto obj : objects)
            {
                Rectangle(hdc,
                    obj._objPos.x - obj._objScale.x / 2,
                    obj._objPos.y - obj._objScale.y / 2,
                    obj._objPos.x + obj._objScale.x / 2,
                    obj._objPos.y + obj._objScale.y / 2);
            }

            // dc�� ���� ���� ������ �ǵ��� (�귯�� ����)
            SelectObject(hdc, dpen);
            SelectObject(hdc, dbrush);

            // �پ� red pen ����
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

                // ������ ���� false�ϰ�� clear���� �ʴ´�.
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
        trigger = true;
        // ��Ʈ �������� �о����
        leftTop.x = LOWORD(pos); // x
        leftTop.y = HIWORD(pos); // y
    }
    break;
    case WM_MOUSEMOVE:
        rightBottom.x = LOWORD(lParam);
        rightBottom.y = HIWORD(lParam);
        InvalidateRect(hWnd, nullptr, true);

        break;

    case WM_LBUTTONUP:
    {
        ObjectInfo info;
        info._objPos = { (leftTop.x + rightBottom.x) / 2, (leftTop.y + rightBottom.y) / 2};
        info._objScale.x = abs(rightBottom.x - leftTop.x);
        info._objScale.y = abs(rightBottom.y - leftTop.y);

        objects.push_back(info);
        trigger = false;
        InvalidateRect(hWnd, nullptr, true);
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
