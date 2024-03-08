#pragma once

#include <memory>
#include "define.h"

class Core
{
public:
	DECLARE_SINGLE(Core);

public:
	int		Init(HWND hWnd, POINT resolution);
	void	Progress();

	const HWND GetHwnd() { return _hwnd; }
	
private:
	void Update();
	void Render();
	
private:
	void UpdateManager();

	void RenderBegin();
	void Rendering();
	void RenderEnd();
	
private:
	void InitWindow();
	void InitManager();
	void InitBitMap();
	
private:
	HWND	_hwnd = 0;
	POINT	_resolution = {};
	HDC		_hdc = 0;
	
	HBITMAP _hbit = 0;
	HDC		_memdc = 0;
};
