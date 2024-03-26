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

	// 이전 프레임의 카운팅과 현재 프레임의 카운팅 값의 차이를 구한다.
	_deltaTime = double(_curCount.QuadPart - _prevCount.QuadPart) / double(_frquency.QuadPart);
	
	// 이전 카운트 값을 현재 값으로 갱신 (다음 계산위함)
	_prevCount = _curCount;

	++_callCount;
	_accTime += _deltaTime; // 누적값은 프레임의 합

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
