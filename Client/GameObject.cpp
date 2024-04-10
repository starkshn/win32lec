#include "pch.h"
#include "GameObject.h"
#include "Texture.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

GameObject* GameObject::Clone()
{
    return nullptr;
}

void GameObject::Update()
{
    
}

void GameObject::Render()
{
    Object::Render();
    
	if (Texture* tex = GetTexture())
	{ 
		uint32 h = (int)tex->GetTexHeight();
		uint32 w = (int)tex->GetTexWidth();
		Vec2 pos = GetPos();
		Vec2 renderPos = GetRenderPos();
		int lx = int(renderPos.x - float(w / 2.f));
		int ly = int(renderPos.y - float(h / 2.f));

		TransparentBlt
		(
			GET_MEMDC,
			int(lx), int(ly), w, h,
			GetTexture()->GetDC(),
			0, 0, w, h,
			RGB(255, 0, 255)
		);
	}
}

void GameObject::Init()
{
}

void GameObject::Begin()
{
}

void GameObject::End()
{
}
