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
	
	// BLACK : 0, 0, 0 (RGB) 초기값은 이렇게 설정된다.
	SetCameraTex(RESOURCE->CreateTexture(L"CameraTexture", uint32(res.x), uint32(res.y)));
}

void Camera::Update()
{
	// target이 있다면 따라가는 함수
	FollowTarget();

	// 방향키 이동 업데이트
	KeyInput();

	// 화면 중앙 좌표와 카메라 LookAt 좌표간의 차이값 계산
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
		// 카메라 효과 시간 누적
		SetCurCameraEffectAccTime(GetCurCameraEffectAccTime() + DT_F);
		
		// 지속시간을 넘어선 경우 효과를 종료 시킴.
		if (GetCurCameraEffectAccTime() >= GetCurCameraEffectDuration())
		{
			ResetCamEF();
			return;
		}
		else
		{
			// effect alpha 0 ~> 255 로 가야한다.
			// 시간에 따른 비율값을 구해야한다.
			SetCurCameraEffectRatio(GetCurCameraEffectAccTime() / GetCurCameraEffectDuration()); // zero division check

			// 알파값 설정
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
		// 등가속도 운동 움직임
		MoveCameraAcceleratedMotion(_cameraEffectAccTime);

		// 일반 선형? 움직임
		// MoveCameraStaticMotion(_cameraAccTime);
	}

	Vec2 res = GET_RESOLUTION;
	Vec2 resCenterPos = res / 2.f;

	// 차이값 (오브젝트들이 렌더를 위해 사용하는 값이다.)
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

	// 현재 보고있는 좌표값 업데이트
	SetCameraCurrentLookAtPos(pos);

	// 움직인 만큼 렌더링 좌표 계산 (오브젝트 들이 사용함)
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
	// 카메라가 봐야할 목표 좌표 설정
	SetCameraDestLookAtPos(pos);

	// 이전 좌표 기록
	SetCameraPrevLookAtPos(GetCameraCurrentLookAtPos());

	// 방향벡터
	_dir = (pos - GetCameraCurrentLookAtPos());
	_dir.Normalize();
	
	// 카메라 이동 거리 설정
	Vec2 destPos = GetCameraDestLookAtPos();
	Vec2 prevPos = GetCameraPrevLookAtPos();
	SetCameraMoveDistance((destPos - prevPos).Length());
	float cameraMoveDis = GetCameraMoveDistance();

	// 카메라 이동 최초의 속도 설정( 거리 / 시간 == V0)
	// 거리 = 속도 * 시간 ( => 속도 = 거리 / 시간) 으로 속도 구함
	SetCameraFollowSpeed(cameraMoveDis / _cameraFollowTime);
	float cameraSpeed = GetCameraFollowSpeed();

	// 카메라 누적 시간 초기화
	_cameraEffectAccTime = 0.f;

	// 초기 속도 설정
	_v0 = cameraSpeed;

	// 가속도 계산
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
