#pragma once

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
	const HDC GetMemDC() { return _memdc; }

	// �Ʒ� �Լ� �� ������ ������ �߻��ϴ���..??
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
	
private:
	HWND	_hwnd = 0;
	POINT	_resolution = {};
	HDC		_hdc = 0;
	
	HBITMAP _hbit = 0;
	HDC		_memdc = 0;
};
