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
