#pragma once
#include "Resources.h"
class Texture : public Resources
{
public:
	Texture();
	virtual ~Texture() override;

private:
	HDC		_dc = 0;			// DC
	HBITMAP _bitMap = 0;		// ∫Ò∆Æ∏ 
};

