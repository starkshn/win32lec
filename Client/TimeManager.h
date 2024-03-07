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
	
	double _deltaTime = 0; // ������ ���� �ð���
	double _accTime = 0;
	UINT _callCount = 0;	// deltaTime�� ������ fps�̴�. (�ʴ� ȣ�� ȸ��)
	UINT _fps = 0;
};

