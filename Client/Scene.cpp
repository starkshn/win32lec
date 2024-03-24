#include "pch.h"
#include "Scene.h"
#include "Object.h"

Scene::Scene()
{

}

Scene::~Scene()
{
	for (uint32 i = 0; i < static_cast<uint32>(OBJECT_TYPE::END); ++i)
	{
		for (uint32 j = 0; j < _sceneObjects[i].size(); ++j)
		{
			if (nullptr != _sceneObjects[i][j])
			{
				delete _sceneObjects[i][j];
			}
		}
	}
}

void Scene::Update()
{
	for (uint32 i = 0; i < (uint32)OBJECT_TYPE::END; ++i)
	{
		for (Object* obj : _sceneObjects[i])
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
	for (uint32 i = 0; i < (uint32)OBJECT_TYPE::END; ++i)
	{
		for (Object* obj : _sceneObjects[i])
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
	for (uint32 i = 0; i < (uint32)OBJECT_TYPE::END; ++i)
	{
		for (Object* obj : _sceneObjects[i])
		{
			if (obj)
			{
				obj->Render();
			}
		}
	}
}


void Scene::InitObjects()
{
	for (uint32 i = 0; i < (uint32)OBJECT_TYPE::END; ++i)
	{
		for (Object* obj : _sceneObjects[i])
		{
			if (obj)
			{
				obj->Init();
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
