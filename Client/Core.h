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

	const HWND	GetHwnd() { return _hwnd; }

private:
	void Update();
	void Render();

private:
	HWND	_hwnd = 0;
	POINT	_resolution = {};
	HDC		_hdc = 0;
};
