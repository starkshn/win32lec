#pragma once

class SelectGDI
{
	DECLARE_SINGLE(SelectGDI);

public:
	void SetBrush(HDC dc, BRUSH_TYPE type);
	void SetPen(HDC dc, PEN_TYPE type);

	void ReleaseBrush();
	void ReleasePen();

private:
	HDC		_dc;
	HBRUSH _defaultBrush;
	HPEN	_defaultPen;
};

