#pragma once

// forward declarations ...
class Object;

class Camera
{
	DECLARE_SINGLE(Camera);

public:
	void Init();
	void Update();

	// 해상도(화면) 정중앙 위치와 현재 카메라 LookAtPos와의 차이값을 계산하는 함수
	void CalDiff();

public:
	void KeyInput();

	const Vec2 GetLookAtPos() { return _lookAtPos; }
	void SetLookAtPos(Vec2 pos) { _lookAtPos = pos; }

	// Scene에서 특정 좌표 클릭시 Dest Look at 설정하는 함수
	const void SetDestLookAtPos(Vec2 pos);

	// SetDestLookAtPos호출시 현재 카메라 LookAt <-> DestLookAt 거리
	float GetCameraMoveDistance() { return _cameraMoveDistance; }
	void SetCameraMoveDistance(float distance) { _cameraMoveDistance = distance; }

	Vec2 GetCameraDestLookAtPos() { return _destLookAtPos; }
	void SetCameraDestLookAtPos(Vec2 pos) { _destLookAtPos = pos; }

	Vec2 GetCameraCurrentLookAtPos() { return _curLookAtPos; }
	void SetCameraCurrentLookAtPos(Vec2 pos) { _curLookAtPos = pos; }

	const Vec2 GetCameraPrevLookAtPos() { return _prevLookAtPos; }
	void SetCameraPrevLookAtPos(Vec2 pos) { _prevLookAtPos = pos; }

	Object* GetTarget()
	{
		if (nullptr != _targetObject)
			return _targetObject;
		else
			return nullptr;
	}
	void SetTarget(Object* obj) { _targetObject = obj; }

	Vec2 GetCameraDiff() { return _diff; }
	Vec2 GetRenderPos(Vec2 objPos) { return objPos - _diff; }

	const float GetCameraFollowSpeed() { return _cameraFollowSpeed; }
	void SetCameraFollowSpeed(float speed) { _cameraFollowSpeed = speed; }

	Vec2 GetRenderPosFromWindowActualPos(Vec2 renderPos)
	{
		return renderPos - _diff;
	}
	Vec2 GetWindowActualPosFromRenderPos(Vec2 actualPos)
	{
		return actualPos + _diff;
	}

	// 시간에 따른 속도를 구함
	void MoveCameraAcceleratedMotion(float time);

	// 시간에 따른 거리를 구함
	void MoveCameraAcceleratedMotion2(float time);

	void MoveCameraStaticMotion(float time);

private:
	Vec2 _lookAtPos		= Vec2(0.f, 0.f);		// 현재 프레임 카메라가 봐야할(목표로 두어야할) 좌표값
	Vec2 _destLookAtPos	= Vec2(0.f, 0.f);		// 현재 프레임 카메라가 목표로 두어야할 좌표값
	Vec2 _curLookAtPos	= Vec2(0.f, 0.f);		// 현재 프레임 카메라가 실제로 봐야할 좌표값
	Vec2 _prevLookAtPos = Vec2(0.f, 0.f);		// 이전 프레임 봐야할 카메라 좌표값
	Vec2 _diff			= Vec2(0.f, 0.f);		// 화면 정중앙 pos와 현재 lookAtPos의 차이값
	Object* _targetObject = nullptr;			// target

	Vec2 _dir = Vec2{};

	float _cameraMoveDistance	= 0.f;			// 변위이자 면적
	float _cameraFollowSpeed	= 500.f;		// 카메라 fllow speed
	float _cameraFollowTime		= 0.5f;			// 카메라가 따라가야하는 시간
	float _cameraAccTime		= 0.f;			// 카메라 누적 시간
	
	// v = v0 - at
	float _v0		= 50.f;						// 처음 속도
	float _a		= 0.f;						// 가속도
	float _curSpeed = 0.f;						// 현재 속도

	bool _flag = false;
};

