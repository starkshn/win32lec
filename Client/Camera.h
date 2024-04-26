#pragma once

struct CameraEffectInfo
{
public:
	// Camera Effect
	CAMERA_EFFECT	_effect = CAMERA_EFFECT::NONE;

	// Camera Effect Duration
	float			_duration = 0.f;

	// Camera Effect Accumulation Time
	float			_accTime = 0.f;
};

// forward declarations ...
class Object;
class Texture;

class Camera
{
	DECLARE_SINGLE(Camera);

public:
	void Init();
	void Update();
	void Render();

public:
	// 해상도(화면) 정중앙 위치와 현재 카메라 LookAtPos와의 차이값을 계산하는 함수
	// 마우스 왼쪽 버튼 클릭시
	void CalDiff_LBTN();

	// 방향키 입력시 화면 정중앙과 이동한 좌표 차이만큼 렌더링 좌표 업데이트
	void CalDiff_DirMove();

public:
	// target이 있다면 쭉 따라가는 함수
	void FollowTarget();
	
	// 방향키 이동 업데이트 함수
	void KeyInput();

	Vec2 GetRenderPosFromWindowActualPos(Vec2 windowPos) { return windowPos - _diff; }
	Vec2 GetWindowActualPosFromRenderPos(Vec2 renderPos) { return renderPos + _diff; }
	
	// Camera Effect
public:
	void ZoomIn();
	void ZoomOut();
	void FadeOut(float duration);
	void FadeIn(float duration);
	
	// cam effect
public:
	Texture*		GetCameraTex()									{ return _cameraTexture;}
	CAMERA_EFFECT	GetCurCameraEffectType()						{ return _curCamEffect; }
	float			GetCurCameraEffectDuration()					{ return _curCamDuration; }
	float			GetCurCameraEffectAccTime()						{ return _curCamAccTime; }
	float			GetCurCameraEffectRatio()						{ return _curCamEffectRatio; }
	int32			GetCurAlpha()									{ return _alphaValue; }

private:
	void			SetCameraTex(Texture* tx)						{ _cameraTexture = tx; }
	void			SetCurCameraEffectType(CAMERA_EFFECT effect)	{ _curCamEffect = effect; }
	void			SetCurCameraEffectDuration(float duration)		{ _curCamDuration = duration; }
	void			SetCurCameraEffectAccTime(float accTime)		{ _curCamAccTime = accTime; }
	void			SetCurCameraEffectRatio(float ratio)			{ _curCamEffectRatio = ratio; }
	void			SetCurAlpha(int32 value)						{ _alphaValue = value; }

private:
	// 카메라 효과 종료시 호출(리셋)
	void ResetCameraEffect();

public:
	// Scene에서 특정 좌표 클릭시 Dest Look at 설정하는 함수
	const void SetDestLookAtPos(Vec2 pos);

	// SetDestLookAtPos호출시 현재 카메라 LookAt <-> DestLookAt 거리
	float		GetCameraMoveDistance()					{ return _cameraMoveDistance; }
	void		SetCameraMoveDistance(float distance)	{ _cameraMoveDistance = distance; }

	Vec2		GetCameraDestLookAtPos()				{ return _destLookAtPos; }
	void		SetCameraDestLookAtPos(Vec2 pos)		{ _destLookAtPos = pos; }

	// 현재 카메라 위치 반환 (현재 보고 있는 정중앙 실제(윈도우) 위치 반환)
	Vec2		GetCameraCurrentLookAtPos()				{ return _curLookAtPos; }
	void		SetCameraCurrentLookAtPos(Vec2 pos)		{ _curLookAtPos = pos; }

	const Vec2	GetCameraPrevLookAtPos()				{ return _prevLookAtPos; }
	void		SetCameraPrevLookAtPos(Vec2 pos)		{ _prevLookAtPos = pos; }

	Object* GetTarget()
	{
		if (nullptr != _targetObject)
			return _targetObject;
		else
			return nullptr;
	}
	void		SetTarget(Object* obj)				{ _targetObject = obj; }

	Vec2		GetCameraDiff()						{ return _diff; }
	Vec2		GetRenderPos(Vec2 objPos)			{ return objPos - _diff; }

	const float GetCameraFollowSpeed()				{ return _cameraFollowSpeed; }
	void		SetCameraFollowSpeed(float speed)	{ _cameraFollowSpeed = speed; }

	// 시간에 따른 속도를 구함
	void		MoveCameraAcceleratedMotion(float time);

	// 시간에 따른 거리를 구함
	void		MoveCameraAcceleratedMotion2(float time);

	void		MoveCameraStaticMotion(float time);

private:
	Vec2				_lookAtPos				= Vec2(0.f, 0.f);		// 현재 프레임 카메라가 봐야할(목표로 두어야할) 좌표값
	Vec2				_destLookAtPos			= Vec2(0.f, 0.f);		// 현재 프레임 카메라가 목표로 두어야할 좌표값
	Vec2				_curLookAtPos			= Vec2(0.f, 0.f);		// 현재 프레임 카메라가 실제로 봐야할 좌표값
	Vec2				_prevLookAtPos			= Vec2(0.f, 0.f);		// 이전 프레임 봐야할 카메라 좌표값
	Vec2				_diff					= Vec2(0.f, 0.f);		// 화면 정중앙 pos와 현재 lookAtPos의 차이값
	Vec2				_dir					= Vec2{};				// 
	Object*				_targetObject			= nullptr;				// target

private:
	float				_cameraMoveDistance		= 0.f;					// 변위이자 면적
	float				_cameraFollowSpeed		= 500.f;				// 카메라 fllow speed
	float				_cameraFollowTime		= 0.5f;					// 카메라가 따라가야하는 시간
	float				_cameraEffectAccTime	= 0.f;					// 카메라 누적 시간
	int32				_alphaValue				= 0;
	
	// 등가속 운동(수정해야함)
private:
	// v = v0 - at
	float				_v0		= 50.f;									// 처음 속도
	float				_a		= 0.f;									// 가속도
	float				_curSpeed = 0.f;								// 현재 속도

	// Mouse LBTN
private:
	bool				_triggerLBTN = false;


	// Camera Effect	
private:
	CameraEffectInfo		_cameraEffectInfo	= {};
	queue<CameraEffectInfo> _cameraEffectQueue;

	CAMERA_EFFECT			_curCamEffect		= CAMERA_EFFECT::NONE;		// 현재 카메라 효과
	float					_curCamDuration		= 0.f;						// 현재 카메라 효과 지속시간
	float					_curCamAccTime		= 0.f;						// 현재 카메라 효과 진행의 누적 시간
	Texture*				_cameraTexture		= nullptr;					// 카메라 텍스쳐 (리소스 매니저로 부터 받은 텍스쳐)
	float					_curCamEffectRatio	= 0.f;						// 현재 카메라 시간에 따른 알파 비율값
	bool					_nowCameraEffecting	= false;					// 현재 효과가 진행중인지
};

