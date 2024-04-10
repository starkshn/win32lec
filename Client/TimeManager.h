#pragma once

class ToolScene;

class TimeManager : public Manager
{
	DECLARE_SINGLE(TimeManager);

	using FuncType = void (*)();

public:
	virtual void Init() override;
	virtual void Update() override;

	double	GetDeltaTime() { return _deltaTime; }
	float	GetDeltaTimeFloat() { return (float)_deltaTime; }
	UINT	GetFPS() { return _fps; }


private:
		
private:
	// 1 frame time : delta time
	LARGE_INTEGER _curCount = {};
	LARGE_INTEGER _prevCount = {};
	LARGE_INTEGER _frquency = {};
	
	double _deltaTime	= 0; // ������ ���� �ð���
	double _accTime		= 0;
	UINT _callCount		= 0;	// deltaTime�� ������ fps�̴�. (�ʴ� ȣ�� ȸ��)
	UINT _fps = 0;
	
private:
	// vector<pair<FuncType, uint32>> _vecCallBackTimer;
};

