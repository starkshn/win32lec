#pragma once

class Core
{
public:
	// define 헤더들을 메크로 앞에 위치하면 링킹 에러나는데 왜 그런지...???
	DECLARE_SINGLE(Core);

public:
	int		Init(HWND hWnd, POINT resolution);
	void	Progress();

public:
	const HWND GetHwnd() { return _hwnd; }
	const HDC GetMemDC() { return _memdc; }
	const HDC GetMainDC() { return _hdc; }

	// 아레 함수 왜 컴파일 에러가 발생하는지..??
	const POINT GetResolution() { return _resolution; }
	
private:
	void Update();
	void Render();
	
private:
	void UpdateManager();

	void RenderBegin();
	void Rendering();
	void RenderEnd();
	
private:
	void InitMainWindowHandle(HWND hwnd);
	void InitResolution(POINT resol);
	void InitWindow();
	void InitManager();
	void InitBitMap();
	void InitGDI();

public:
	const HBRUSH GetBrush(BRUSH_TYPE type) { return _brushes[(UINT)type]; }
	const HPEN GetPen(PEN_TYPE type) { return _pens[(UINT)type]; }

private:
	void CreateBrushesAndPen();
	
private:
	HWND	_hwnd = 0;
	POINT	_resolution = {};
	HDC		_hdc = 0;
	
	HBITMAP _hbit = 0;
	HDC		_memdc = 0;

private:
	// brush, pen
	HBRUSH _brushes[(UINT)BRUSH_TYPE::END];
	HPEN _pens[(UINT)PEN_TYPE::END];
};
