#pragma once

#include "Texture.h"

class Core
{
public:
	// define ������� ��ũ�� �տ� ��ġ�ϸ� ��ŷ �������µ� �� �׷���...???
	DECLARE_SINGLE(Core);

public:
	int		Init(HWND hWnd, POINT resolution);
	void	Progress();

public:
	const HWND GetHwnd() { return _hwnd; }
	const HDC GetMemDC() 
	{ 
		return _memdc; 
		// return _backBufferTexture->GetDC();
	}
	const HDC GetMainDC() { return _hdc; }
	const Vec2 GetResolution() { return Vec2(float(_resolution.x), float(_resolution.y)); }
	
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
	void InitBitMap();		// Create Bitmap
	void InitGDI();

public:
	const HBRUSH GetBrush(BRUSH_TYPE type) { return _brushes[(UINT)type]; }
	const HPEN GetPen(PEN_TYPE type) { return _pens[(UINT)type]; }

private:
	void CreateBrushesAndPen();
	
private:
	HWND	_hwnd = 0;
	HDC		_hdc = 0;
	POINT	_resolution = {};
	
	// ���� �̷����� �ƴ϶�
	HBITMAP _hbit = 0;
	HDC		_memdc = 0;

	// �Ʒ�ó�� texture�� �ϳ� ��� �ִ°Ͱ� ����.
	Texture* _backBufferTexture = nullptr;

private:
	// brush, pen
	HBRUSH _brushes[(UINT)BRUSH_TYPE::END];
	HPEN _pens[(UINT)PEN_TYPE::END];
};
