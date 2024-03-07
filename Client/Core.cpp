#include "pch.h"
#include "Core.h"
#include "Object.h"

Object obj;

Core::Core()
{

}

Core::~Core()
{
	ReleaseDC(_hwnd, _hdc);
}

int Core::Init(HWND hWnd, POINT resolution)
{
	_hwnd = hWnd;
	_resolution = resolution;

	// Window Size Calculate
	RECT rc = {0, 0, _resolution .x, _resolution .y};
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	int cx = rc.right - rc.left;
	int cy = rc.bottom - rc.top;
	SetWindowPos(_hwnd, nullptr, 300, 100, cx, cy, 0);

	_hdc = GetDC(_hwnd);

	obj.SetScale(Vec2{ 100, 100 });
	obj.SetPos(Vec2{ int(_resolution.x / 2), int(_resolution.x  / 2)});

	// Manager
	GET_SINGLE(KeyManager)->Init();
	GET_SINGLE(TimeManager)->Init();

	return S_OK;
}

void Core::Progress()
{
	// Manager Updates
	GET_SINGLE(KeyManager)->Update();
	GET_SINGLE(TimeManager)->Update();

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
	Rectangle
	(
		_hdc, 
		obj.GL,
		obj.GT,
		obj.GR,
		obj.GB
	);
}
