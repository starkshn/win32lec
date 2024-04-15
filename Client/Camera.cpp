#include "pch.h"
#include "Camera.h"
#include "Object.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

void Camera::Init()
{
	auto res = GET_RESOLUTION;
	SetCameraCurrentLookAtPos(res / 2.f);
	SetCameraPrevLookAtPos(res / 2.f);
	SetCameraDestLookAtPos(res / 2.f);
}

void Camera::Update()
{
	// target�� �ִٸ� ���󰡴� �Լ�
	FollowTarget();

	// ����Ű �̵� ������Ʈ
	KeyInput();

	// ȭ�� �߾� ��ǥ�� ī�޶� LookAt ��ǥ���� ���̰� ���
	if (_triggerLBTN)
		CalDiff_LBTN();
}

void Camera::CalDiff_LBTN()
{
	_cameraAccTime += DT_F;
	
	if (_cameraAccTime >= _cameraFollowTime)
	{
		SetCameraCurrentLookAtPos(GetCameraCurrentLookAtPos());
		_triggerLBTN = false;
	}
	else
	{
		// ��ӵ� � ������
		MoveCameraAcceleratedMotion(_cameraAccTime);

		// �Ϲ� ����? ������
		// MoveCameraStaticMotion(_cameraAccTime);
	}

	Vec2 res = GET_RESOLUTION;
	Vec2 resCenterPos = res / 2.f;

	// ���̰� (������Ʈ���� ������ ���� ����ϴ� ���̴�.)
	_diff = GetCameraCurrentLookAtPos() - resCenterPos;
}

void Camera::CalDiff_DirMove()
{
	Vec2 res = GET_RESOLUTION;
	Vec2 resCenterPos = res / 2.f;
	_diff = GetCameraCurrentLookAtPos() - resCenterPos;
}

void Camera::FollowTarget()
{
	Object* targetObject = GetTarget();
	if (nullptr != targetObject)
	{
		if (targetObject->GetThisObjectWillDelete())
		{
			SetTarget(nullptr);
		}
		else
		{
			SetCameraCurrentLookAtPos(targetObject->GetPos());
		}
	}
}

void Camera::KeyInput()
{
	Vec2 pos = GetCameraCurrentLookAtPos();

	if (KEY_HOLD(KEYES::LEFT))
	{
		pos.x -= 500.f * DT_F;
	}

	if (KEY_HOLD(KEYES::UP))
	{
		pos.y -= 500.f * DT_F;
	}

	if (KEY_HOLD(KEYES::DOWN))
	{
		pos.y += 500.f * DT_F;
	}

	if (KEY_HOLD(KEYES::RIGHT))
	{
		pos.x += 500.f * DT_F;
	}

	// ���� �����ִ� ��ǥ�� ������Ʈ
	SetCameraCurrentLookAtPos(pos);

	// ������ ��ŭ ������ ��ǥ ��� (������Ʈ ���� �����)
	CalDiff_DirMove();
}

void Camera::ZoomIn()
{
	
}

void Camera::ZoomOut()
{

}

const void Camera::SetDestLookAtPos(Vec2 pos)
{
	// ī�޶� ������ ��ǥ ��ǥ ����
	SetCameraDestLookAtPos(pos);

	// ���� ��ǥ ���
	SetCameraPrevLookAtPos(GetCameraCurrentLookAtPos());

	// ���⺤��
	_dir = (pos - GetCameraCurrentLookAtPos());
	_dir.Normalize();
	
	// ī�޶� �̵� �Ÿ� ����
	Vec2 destPos = GetCameraDestLookAtPos();
	Vec2 prevPos = GetCameraPrevLookAtPos();
	SetCameraMoveDistance((destPos - prevPos).Length());
	float cameraMoveDis = GetCameraMoveDistance();

	// ī�޶� �̵� ������ �ӵ� ����( �Ÿ� / �ð� == V0)
	// �Ÿ� = �ӵ� * �ð� ( => �ӵ� = �Ÿ� / �ð�) ���� �ӵ� ����
	SetCameraFollowSpeed(cameraMoveDis / _cameraFollowTime);
	float cameraSpeed = GetCameraFollowSpeed();

	// ī�޶� ���� �ð� �ʱ�ȭ
	_cameraAccTime = 0.f;

	// �ʱ� �ӵ� ����
	_v0 = cameraSpeed;

	// ���ӵ� ���
	_a = (0 - _v0) / _cameraFollowTime;

	_triggerLBTN = true;
}

void Camera::MoveCameraAcceleratedMotion(float time)
{
	Vec2 curPos = GetCameraCurrentLookAtPos();
	
	_curSpeed = _v0 + _a * time;
	
	Vec2 nextPos = curPos + _dir * _curSpeed * DT_F;

	SetCameraCurrentLookAtPos(nextPos);
}

void Camera::MoveCameraAcceleratedMotion2(float time)
{
	// _v0 * time + (_a * pow(time, 2)) / 2;
}

void Camera::MoveCameraStaticMotion(float time)
{
	Vec2 curPos = GetCameraCurrentLookAtPos();

	Vec2 nextPos = curPos + _dir * GetCameraFollowSpeed() * DT_F;

	SetCameraCurrentLookAtPos(nextPos);
}
