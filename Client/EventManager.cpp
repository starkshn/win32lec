#include "pch.h"
#include "EventManager.h"

EventManager::EventManager()
{

}

EventManager::~EventManager()
{

}

void EventManager::Init()
{
}

void EventManager::Update()
{
	// ���� �����ӿ��� ����ص� Dead Object���� ������
	for (uint32 i = 0; i < _vecDeleteObjects.size(); ++i)
	{
		delete _vecDeleteObjects[i];
	}
	_vecDeleteObjects.clear();


	// Eventó��
	for (uint32 i = 0; i < _vecEvents.size(); ++i)
	{
		Execute(_vecEvents[i]);
	}
	_vecEvents.clear();
}

void EventManager::Execute(const EVENT_INFO& _event)
{
	switch (_event._eventType)
	{
		case EVENT_TYPE::CREATE_OBJECT:
		{
			// lParam : Object Address
			// rParam : Object Type
			
			Object* obj = (Object*)(_event._lParam);
			OBJECT_TYPE type = (OBJECT_TYPE)(_event._rParam);
			
			 SCENE->GetCurrentScene()->AddObject(obj, type);
		}
		break;
		case EVENT_TYPE::DELETE_OBJECT:
		{
			Object* delObject = (Object*)(_event._lParam);
			OBJECT_TYPE type = (OBJECT_TYPE)(_event._rParam);
			delObject->SetThisObjectWillDelete();
			_vecDeleteObjects.push_back(delObject);
		}
		break;
		case EVENT_TYPE::SCENE_CHANGE:
		{

		}
		break;
	default:
		break;
	}
}
