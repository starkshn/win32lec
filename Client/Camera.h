#pragma once

// forward declarations ...
class Object;

class Camera
{
	DECLARE_SINGLE(Camera);

public:
	void Init();
	void Update();

	// �ػ�(ȭ��) ���߾� ��ġ�� ���� ī�޶� LookAtPos���� ���̰��� ����ϴ� �Լ�
	void CalDiff();

public:
	void KeyInput();

	const Vec2 GetLookAtPos() { return _lookAtPos; }
	void SetLookAtPos(Vec2 pos) { _lookAtPos = pos; }

	// Scene���� Ư�� ��ǥ Ŭ���� Dest Look at �����ϴ� �Լ�
	const void SetDestLookAtPos(Vec2 pos);

	// SetDestLookAtPosȣ��� ���� ī�޶� LookAt <-> DestLookAt �Ÿ�
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

	// �ð��� ���� �ӵ��� ����
	void MoveCameraAcceleratedMotion(float time);

	// �ð��� ���� �Ÿ��� ����
	void MoveCameraAcceleratedMotion2(float time);

	void MoveCameraStaticMotion(float time);

private:
	Vec2 _lookAtPos		= Vec2(0.f, 0.f);		// ���� ������ ī�޶� ������(��ǥ�� �ξ����) ��ǥ��
	Vec2 _destLookAtPos	= Vec2(0.f, 0.f);		// ���� ������ ī�޶� ��ǥ�� �ξ���� ��ǥ��
	Vec2 _curLookAtPos	= Vec2(0.f, 0.f);		// ���� ������ ī�޶� ������ ������ ��ǥ��
	Vec2 _prevLookAtPos = Vec2(0.f, 0.f);		// ���� ������ ������ ī�޶� ��ǥ��
	Vec2 _diff			= Vec2(0.f, 0.f);		// ȭ�� ���߾� pos�� ���� lookAtPos�� ���̰�
	Object* _targetObject = nullptr;			// target

	Vec2 _dir = Vec2{};

	float _cameraMoveDistance	= 0.f;			// �������� ����
	float _cameraFollowSpeed	= 500.f;		// ī�޶� fllow speed
	float _cameraFollowTime		= 0.5f;			// ī�޶� ���󰡾��ϴ� �ð�
	float _cameraAccTime		= 0.f;			// ī�޶� ���� �ð�
	
	// v = v0 - at
	float _v0		= 50.f;						// ó�� �ӵ�
	float _a		= 0.f;						// ���ӵ�
	float _curSpeed = 0.f;						// ���� �ӵ�

	bool _flag = false;
};

