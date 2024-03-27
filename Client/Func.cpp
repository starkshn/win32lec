#include "pch.h"
#include "Func.h"

void CreateObject(Object* obj, OBJECT_TYPE objType)
{
	EVENT_INFO evn = { };
	evn._eventType = EVENT_TYPE::CREATE_OBJECT;
	
	// �ּҰ��� DWORD_PTR�� ����ȯ �Ͽ� ���
	evn._lParam = (DWORD_PTR)obj;
	evn._rParam = (DWORD_PTR)objType;
	
	EVENT->AddEvent(evn);
}

void DeleteObject(Object* obj)
{
	EVENT_INFO evn = { };
	evn._eventType = EVENT_TYPE::DELETE_OBJECT;

	evn._lParam = (DWORD_PTR)obj;
	evn._rParam = (DWORD_PTR)obj->GetType();

	EVENT->AddEvent(evn);
}

void ChnageScene_EV(SCENE_TYPE destType)
{
	EVENT_INFO evn = { };
	evn._eventType = EVENT_TYPE::SCENE_CHANGE;
	evn._lParam = (DWORD_PTR)destType;

	EVENT->AddEvent(evn);
}
