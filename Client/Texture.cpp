#include "pch.h"
#include "Texture.h"

Texture::Texture()
{

}

Texture::~Texture()
{
	DeleteDC(GetDC());
	DeleteObject(GetBitMap());
}

void Texture::CreateBitmap(uint32 width, uint32 height)
{
	// Core.h InitBitmap과 동일하다
	_bitMap = CreateCompatibleBitmap(GET_MAIN_DC, width, height);
	_dc = CreateCompatibleDC(GET_MAIN_DC);
	assert(_bitMap);

	// 교체
	HBITMAP prevBit = (HBITMAP)SelectObject(_dc, _bitMap);
	DeleteObject(prevBit);

	// 비트맵 정보
	// 무슨 시스템 함수인가
	GetObject(_bitMap, sizeof(BITMAP), &_bitMapInfo);
}