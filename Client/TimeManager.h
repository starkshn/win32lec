#pragma once

class TimeManager
{
	DECLARE_SINGLE(TimeManager);

public:
	void	Init();
	void	Update();

	double	GetDeltaTime() { return _deltaTime; }
	float	GetDeltaTimeFloat() { return (float)_deltaTime; }
	UINT	GetFPS() { return _fps; }
		
private:
	// 1 frame time : delta time
	LARGE_INTEGER _curCount = {};
	LARGE_INTEGER _prevCount = {};
	LARGE_INTEGER _frquency = {};
	
	double _deltaTime = 0; // 프레임 간의 시간값
	double _accTime = 0;
	UINT _callCount = 0;	// deltaTime의 역수가 fps이다. (초당 호출 회수)
	UINT _fps = 0;
};

