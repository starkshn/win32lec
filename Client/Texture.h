#pragma once
#include "Resources.h"
class Texture : public Resources
{
private:
	Texture();
	virtual ~Texture() override;
	friend class ResourceManager;

public:
	void CreateBitmap(uint32 width, uint32 height);
};

