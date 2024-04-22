#include "pch.h"
#include "UnitObject.h"


UnitObject::UnitObject()
{

}

UnitObject::~UnitObject()
{

}

UnitObject* UnitObject::Clone()
{
	return nullptr;
}


void UnitObject::Update()
{
	GameObject::Update();
}

void UnitObject::Render()
{
	GameObject::Render();
}

void UnitObject::Init()
{

}

void UnitObject::Begin()
{

}

void UnitObject::End()
{

}
