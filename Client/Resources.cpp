#include "pch.h"
#include "Resources.h"

Resources::Resources()
{

}

Resources::~Resources()
{
	
}

void Resources::LoadResource(const FILE_TYPE ftype, const RES type, const wstring& path)
{
	switch (ftype)
	{
		case FILE_TYPE::BITMAP:
		{
			LoadFile(type, path);
		}
		break;
		case FILE_TYPE::PNG:
		{
			
		}
		break;
		case FILE_TYPE::JPG:
		{

		}
		break;
	default:
		break;
	}
}

void Resources::LoadFile(const RES type, const wstring& path)
{
	switch (type)
	{
		case RES::TEXTURE:
		{
			// ���Ϸ� ���� �ε��� �����͸� ��Ʈ������ ����
			_bitMap = (HBITMAP)LoadImage(nullptr, path.c_str(), IMAGE_BITMAP, 0 ,0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

			assert(_bitMap);

			// ��Ʈ�ʰ� DC����
			_dc = CreateCompatibleDC(GET_MAIN_DC);
			HBITMAP temp = (HBITMAP)SelectObject(_dc, _bitMap);
			DeleteObject(temp);
			
			// ���μ��� ����
			GetObject(_bitMap, sizeof(BITMAP), &_bitMapInfo);
		}
		break;
		case RES::SOUND:
		{

		}
		break;
	default:
		break;
	}
}

