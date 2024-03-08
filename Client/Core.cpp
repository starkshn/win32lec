#include "pch.h"
#include "Core.h"
#include "Object.h"

Object obj;

Core::Core()
{

}

Core::~Core()
{
	// Release...
	ReleaseDC(_hwnd, _hdc);

	DeleteDC(_memdc);
	DeleteObject(_hbit);
}

int Core::Init(HWND hWnd, POINT resolution)
{
	_hwnd = hWnd;
	_resolution = resolution;

	InitWindow();
	InitManager();
	InitBitMap();

	obj.SetScale(Vec2{ 100, 100 });
	obj.SetPos(Vec2{ int(_resolution.x / 2), int(_resolution.x  / 2)});

	return S_OK;
}

void Core::Progress()
{
	UpdateManager();

	// Core
	Update();
	Render();
}

void Core::Update()
{
	auto pos = obj.GetPos();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		pos._x -= 100.f * DT;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		pos._x += 100.f * DT;
	}

	obj.SetPos(pos);
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
}

void Core::RenderBegin()
{
	// clear bitmap
	Rectangle
	(_memdc, -1, -1, _resolution.x + 1, _resolution.y + 1);
}

void Core::Rendering()
{
	// render objects (draw objects)
	Rectangle(_memdc, obj.GL, obj.GT, obj.GR, obj.GB);
}

void Core::RenderEnd()
{
	// copy prev to main window
	BitBlt
	(
		_hdc,
		0, 0, _resolution.x, _resolution.y, 
		_memdc, 0, 0, SRCCOPY
	);
}

void Core::InitWindow()
{
	// Window Size Calculate
	RECT rc = { 0, 0, _resolution.x, _resolution.y };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	int cx = rc.right - rc.left;
	int cy = rc.bottom - rc.top;
	SetWindowPos(_hwnd, nullptr, 300, 100, cx, cy, 0);

	_hdc = GetDC(_hwnd);
}

void Core::InitManager()
{
	GET_SINGLE(KeyManager)->Init();
	GET_SINGLE(TimeManager)->Init();
}

void Core::InitBitMap()
{
	// double buffering
	_hbit = CreateCompatibleBitmap(_hdc, _resolution.x, _resolution.y);
	_memdc = CreateCompatibleDC(_hdc);

	// ±³Ã¼
	HBITMAP prevBit = (HBITMAP)SelectObject(_memdc, _hbit);
	DeleteObject(prevBit);
}
