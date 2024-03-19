#include "pch.h"
#include "Scene.h"
#include "Object.h"

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::Update()
{
	for (int i = 0; i < (uint32)OBJECT_TYPE::END; ++i)
	{
		for (auto obj : _sceneObjects[i])
		{
			if (obj)
			{
				obj->Update();
			}
		}
	}
}

void Scene::FinalUpdate()
{
	for (int i = 0; i < (uint32)OBJECT_TYPE::END; ++i)
	{
		for (auto obj : _sceneObjects[i])
		{
			if (obj)
			{
				obj->FinalUpdate();
			}
		}
	}
}

void Scene::Render()
{
	for (int i = 0; i < (uint32)OBJECT_TYPE::END; ++i)
	{
		for (auto obj : _sceneObjects[i])
		{
			if (obj)
			{
				obj->Render();
			}
		}
	}
}


void Scene::RemoveObject()
{
}

void Scene::FindObject()
{
}
