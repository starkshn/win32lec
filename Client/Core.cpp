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

	// 아래는 각 매니저에 구현 만되어 있고 사용하지 않는다.
	PATH->Update();
	RESOURCE->Update();

	// Manager는 아니지만 EVENT 다음으로 가장 마지막 호출 해준다.
	// 이곳에서 RenderPos가 정해짐
	// 이후 Comp 에서는 이곳의 RenderPos를 쓴다.
	CAMERA->Update();

	// EventManager의 경우 RenderEnd에서 진행

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

	// 모든 프레임은 프레임의 가장 마지막에 처리한다.
	// 이벤트 지연 처리
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
	// _hdc는 현재 윈도우의 device context이다.
	_hbit = CreateCompatibleBitmap(_hdc, _resolution.x, _resolution.y);
	_memdc = CreateCompatibleDC(_hdc);

	// 교체
	HBITMAP prevBit = (HBITMAP)SelectObject(_memdc, _hbit);
	DeleteObject(prevBit);
}

void Core::InitGDI()
{
	CreateBrushesAndPen();
}

void Core::CreateBrushesAndPen()
{
	// 삭제 안해도 된다.
	_brushes[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	
	_pens[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	_pens[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	_pens[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

}
