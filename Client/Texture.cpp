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
	// Core.h InitBitmap�� �����ϴ�
	_bitMap = CreateCompatibleBitmap(GET_MAIN_DC, width, height);
	_dc = CreateCompatibleDC(GET_MAIN_DC);
	assert(_bitMap);

	// ��ü
	HBITMAP prevBit = (HBITMAP)SelectObject(_dc, _bitMap);
	DeleteObject(prevBit);

	// ��Ʈ�� ����
	// ���� �ý��� �Լ��ΰ�
	GetObject(_bitMap, sizeof(BITMAP), &_bitMapInfo);
}