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
	// target이 있다면 따라가는 함수
	FollowTarget();

	// 방향키 이동 업데이트
	KeyInput();

	// 화면 중앙 좌표와 카메라 LookAt 좌표간의 차이값 계산
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
		// 등가속도 운동 움직임
		MoveCameraAcceleratedMotion(_cameraAccTime);

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
	_cameraAccTime = 0.f;

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
