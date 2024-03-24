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
	for (size_t i = 0; i < _vecEvents.size(); ++i)
	{
		Execute(_vecEvents[i]);
	}
}

void EventManager::Execute(const EVENT_INFO& _event)
{
	switch (_event._eventType)
	{
		case EVENT_TYPE::CREATE_OBJECT:
		{
			// lParam : Object Address
			// rParam : Object Type
			
			OBJECT_TYPE type = (OBJECT_TYPE)(_event._rParam);
			
			// SCENE->GetCurrentScene()->AddObject(, type);
		}
		break;
		case EVENT_TYPE::DELETE_OBJECT:
		{

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
