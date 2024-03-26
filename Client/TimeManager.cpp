#include "pch.h"
#include "TimeManager.h"

TimeManager::TimeManager()
	: 
	_curCount{},
	_frquency{}
{

}

TimeManager::~TimeManager()
{

}

void TimeManager::Init()
{
	// prev counts
	QueryPerformanceCounter(&_prevCount);

	// 1 per second counts 
	QueryPerformanceFrequency(&_frquency);
}

void TimeManager::Update()
{
	QueryPerformanceCounter(&_curCount);

	// ���� �������� ī���ð� ���� �������� ī���� ���� ���̸� ���Ѵ�.
	_deltaTime = double(_curCount.QuadPart - _prevCount.QuadPart) / double(_frquency.QuadPart);
	
	// ���� ī��Ʈ ���� ���� ������ ���� (���� �������)
	_prevCount = _curCount;

	++_callCount;
	_accTime += _deltaTime; // �������� �������� ��

	if (_accTime >= 1.0)
	{
		wchar_t buffer[255] = {};
		swprintf_s(buffer, L"FPS : %d, DeltaTime : %f", FPS, DT);
		SetWindowText(GET_WINDOW_HANDLE, buffer);

		_fps = _callCount;
		_accTime = 0;
		_callCount = 0;
	}

#ifdef _DEBUG
	if (_deltaTime > (1.f / 60))
	{
		_deltaTime = (1.f / 60);
	}
#endif
}
