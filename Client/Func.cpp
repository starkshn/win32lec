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
