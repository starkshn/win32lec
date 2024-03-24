#include "pch.h"
#include "Func.h"

void CreateObject(Object* obj, OBJECT_TYPE objType)
{
	EVENT_INFO evn = { };
	evn._eventType = EVENT_TYPE::CREATE_OBJECT;
	
	// 주소값을 DWORD_PTR로 형변환 하여 사용
	evn._lParam = (DWORD_PTR)obj;
	evn._rParam = (DWORD_PTR)objType;
	
	EVENT->AddEvent(evn);
}
