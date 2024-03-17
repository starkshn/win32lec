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
}

int Core::Init(HWND hWnd, POINT resolution)
{
	// Init Window Handle && Set Resolution
	InitMainWindowHandle(hWnd);
	InitResolution(resolution);
	InitWindow();
	InitManager();
	InitBitMap();

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
	GET_SINGLE(KeyManager)->Update();
	GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(SceneManager)->Update();
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
	SetWindowPos(_hwnd, nullptr, 300, 100, cx, cy, 0);

	// get device context
	_hdc = GetDC(_hwnd);
}

void Core::InitManager()
{
	GET_SINGLE(KeyManager)->Init();
	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(SceneManager)->Init();
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
