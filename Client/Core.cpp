#include "pch.h"
#include "Core.h"
#include "Object.h"

Core::Core()
{

}

Core::~Core()
{
	// Release Objects
	ReleaseDC(_hwnd, _hdc);

	DeleteDC(_memdc);
	DeleteObject(_hbit);

	for (int i = 0; i < (UINT)BRUSH_TYPE::END; ++i)
	{
		DeleteObject(_brushes[(UINT)i]);
	}

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(_pens[(UINT)i]);
	}
}

int Core::Init(HWND hWnd, POINT resolution)
{
	// Init Window Handle && Set Resolution
	InitMainWindowHandle(hWnd);
	InitResolution(resolution);
	InitWindow();
	InitManager();
	InitBitMap();
	InitGDI();

	return S_OK;
}

void Core::Progress()
{
	Update();
	Render();
}

void Core::Update()
{
	UpdateManager();
}

void Core::Render()
{
	RenderBegin();
	Rendering();
	RenderEnd();
}

void Core::UpdateManager()
{
	// Manager Updates
	TIME->Update();
	KEY->Update();
	SCENE->Update();
	COLLISION->Update();
	UI_MANAGER->Update();

	// �Ʒ��� �� �Ŵ����� ���� ���Ǿ� �ְ� ������� �ʴ´�.
	PATH->Update();
	RESOURCE->Update();

	// Manager�� �ƴ����� EVENT �������� ���� ������ ȣ�� ���ش�.
	// �̰����� RenderPos�� ������
	// ���� Comp ������ �̰��� RenderPos�� ����.
	CAMERA->Update();

	// EventManager�� ��� RenderEnd���� ����

	BOARD->Update();
}

void Core::RenderBegin()
{
	// clear bitmap
	Rectangle(_memdc, -1, -1, _resolution.x + 1, _resolution.y + 1);
}

void Core::Rendering()
{
	// render objects
	
	// TODO
	GET_SINGLE(SceneManager)->Render();
}

void Core::RenderEnd()
{
	// copy prev to main window
	BitBlt(_hdc, 0, 0, _resolution.x, _resolution.y, _memdc, 0, 0, SRCCOPY);

	// ��� �������� �������� ���� �������� ó���Ѵ�.
	// �̺�Ʈ ���� ó��
	EVENT->Update();
}

void Core::InitMainWindowHandle(HWND hwnd)
{
	_hwnd = hwnd;
}

void Core::InitResolution(POINT resol)
{
	_resolution = resol;
}

void Core::InitWindow()
{
	// Window Size Calculate
	RECT rc = { 0, 0, _resolution.x, _resolution.y };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	int cx = rc.right - rc.left;
	int cy = rc.bottom - rc.top;

	SetWindowPos(_hwnd, nullptr, 100, 100, cx, cy, 0);

	// get device context
	_hdc = GetDC(_hwnd);
}

void Core::InitManager()
{
	KEY->Init();
	TIME->Init();
	PATH->Init();
	RESOURCE->Init();
	SCENE->Init();
	COLLISION->Init();
	CAMERA->Init();
	EVENT->Init();
	BOARD->Init();
}

void Core::InitBitMap()
{
	// double buffering
	// _hdc�� ���� �������� device context�̴�.
	_hbit = CreateCompatibleBitmap(_hdc, _resolution.x, _resolution.y);
	_memdc = CreateCompatibleDC(_hdc);

	// ��ü
	HBITMAP prevBit = (HBITMAP)SelectObject(_memdc, _hbit);
	DeleteObject(prevBit);
}

void Core::InitGDI()
{
	CreateBrushesAndPen();
}

void Core::CreateBrushesAndPen()
{
	// ���� ���ص� �ȴ�.
	_brushes[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	
	_pens[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	_pens[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	_pens[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

}
