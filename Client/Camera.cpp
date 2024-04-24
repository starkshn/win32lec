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
	
	// BLACK : 0, 0, 0 (RGB) �ʱⰪ�� �̷��� �����ȴ�.
	SetCameraTex(RESOURCE->CreateTexture(L"CameraTexture", uint32(res.x), uint32(res.y)));
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

void Camera::Render()
{
	/*if (_cameraEffectQueue.empty() == false)
	{
		_nowCameraEffecting = true;

		CameraEffectInfo curCamInfo = _cameraEffectQueue.front();

		SetCurCameraEffectType(curCamInfo._effect);
		SetCurCameraEffectDuration(curCamInfo._duration);
		SetCurCameraEffectAccTime(curCamInfo._accTime);
	}
	else return;*/

	// Exception
	if (GetCurCameraEffectType() == CAMERA_EFFECT::NONE) return;

	if (GetCurCameraEffectType() == CAMERA_EFFECT::FADE_OUT)
	{
		// ī�޶� ȿ�� �ð� ����
		SetCurCameraEffectAccTime(GetCurCameraEffectAccTime() + DT_F);
		
		// ���ӽð��� �Ѿ ��� ȿ���� ���� ��Ŵ.
		if (GetCurCameraEffectAccTime() >= GetCurCameraEffectDuration())
		{
			ResetCamEF();
			return;
		}
		else
		{
			// effect alpha 0 ~> 255 �� �����Ѵ�.
			// �ð��� ���� �������� ���ؾ��Ѵ�.
			SetCurCameraEffectRatio(GetCurCameraEffectAccTime() / GetCurCameraEffectDuration()); // zero division check

			// ���İ� ����
			SetCurAlpha(int32(255.f * GetCurCameraEffectRatio()));
		}
	}

	if (GetCurCameraEffectType() == CAMERA_EFFECT::FADE_IN)
	{
		SetCurCameraEffectAccTime(GetCurCameraEffectAccTime() + DT_F);
		if (GetCurCameraEffectAccTime() >= GetCurCameraEffectDuration())
		{
			ResetCamEF();
			return;
		}
		else
		{
			SetCurCameraEffectRatio(GetCurCameraEffectAccTime() / GetCurCameraEffectDuration()); // zero division check
			SetCurAlpha(int32(255.f * (1.f - GetCurCameraEffectRatio())));
		}
	}
	
	int32 width = _cameraTexture->GetTexWidth();
	int32 height = _cameraTexture->GetTexHeight();

	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = GetCurAlpha();
	
	AlphaBlend
	(
		GET_MEMDC,
		int32(0), int32(0), int32(width), int32(height),
		GetCameraTex()->GetDC(),
		int32(0), int32(0), int32(width), int32(height),
		bf
	);
}

void Camera::CalDiff_LBTN()
{
	_cameraEffectAccTime += DT_F;
	
	if (_cameraEffectAccTime >= _cameraFollowTime)
	{
		SetCameraCurrentLookAtPos(GetCameraCurrentLookAtPos());
		_triggerLBTN = false;
	}
	else
	{
		// ��ӵ� � ������
		MoveCameraAcceleratedMotion(_cameraEffectAccTime);

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

void Camera::FadeOut(float duration)
{
	_cameraEffectQueue.push(CameraEffectInfo{CAMERA_EFFECT::FADE_OUT, duration, 0.f});
	SetCurCameraEffectType(CAMERA_EFFECT::FADE_OUT);
	SetCurCameraEffectAccTime(0.f);
	SetCurCameraEffectDuration(duration);
	SetCurCameraEffectRatio(0.f);
}

void Camera::FadeIn(float duration)
{
	_cameraEffectQueue.push(CameraEffectInfo{ CAMERA_EFFECT::FADE_IN, duration, 0.f });
}

void Camera::ResetCamEF()
{
	SetCurCameraEffectType(CAMERA_EFFECT::NONE);
	SetCurCameraEffectAccTime(0.f);
	SetCurCameraEffectDuration(0.0000001f);
	SetCurCameraEffectRatio(0.f);
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
	_cameraEffectAccTime = 0.f;

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
