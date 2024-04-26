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
	// �ػ�(ȭ��) ���߾� ��ġ�� ���� ī�޶� LookAtPos���� ���̰��� ����ϴ� �Լ�
	// ���콺 ���� ��ư Ŭ����
	void CalDiff_LBTN();

	// ����Ű �Է½� ȭ�� ���߾Ӱ� �̵��� ��ǥ ���̸�ŭ ������ ��ǥ ������Ʈ
	void CalDiff_DirMove();

public:
	// target�� �ִٸ� �� ���󰡴� �Լ�
	void FollowTarget();
	
	// ����Ű �̵� ������Ʈ �Լ�
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
	// ī�޶� ȿ�� ����� ȣ��(����)
	void ResetCameraEffect();

public:
	// Scene���� Ư�� ��ǥ Ŭ���� Dest Look at �����ϴ� �Լ�
	const void SetDestLookAtPos(Vec2 pos);

	// SetDestLookAtPosȣ��� ���� ī�޶� LookAt <-> DestLookAt �Ÿ�
	float		GetCameraMoveDistance()					{ return _cameraMoveDistance; }
	void		SetCameraMoveDistance(float distance)	{ _cameraMoveDistance = distance; }

	Vec2		GetCameraDestLookAtPos()				{ return _destLookAtPos; }
	void		SetCameraDestLookAtPos(Vec2 pos)		{ _destLookAtPos = pos; }

	// ���� ī�޶� ��ġ ��ȯ (���� ���� �ִ� ���߾� ����(������) ��ġ ��ȯ)
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

	// �ð��� ���� �ӵ��� ����
	void		MoveCameraAcceleratedMotion(float time);

	// �ð��� ���� �Ÿ��� ����
	void		MoveCameraAcceleratedMotion2(float time);

	void		MoveCameraStaticMotion(float time);

private:
	Vec2				_lookAtPos				= Vec2(0.f, 0.f);		// ���� ������ ī�޶� ������(��ǥ�� �ξ����) ��ǥ��
	Vec2				_destLookAtPos			= Vec2(0.f, 0.f);		// ���� ������ ī�޶� ��ǥ�� �ξ���� ��ǥ��
	Vec2				_curLookAtPos			= Vec2(0.f, 0.f);		// ���� ������ ī�޶� ������ ������ ��ǥ��
	Vec2				_prevLookAtPos			= Vec2(0.f, 0.f);		// ���� ������ ������ ī�޶� ��ǥ��
	Vec2				_diff					= Vec2(0.f, 0.f);		// ȭ�� ���߾� pos�� ���� lookAtPos�� ���̰�
	Vec2				_dir					= Vec2{};				// 
	Object*				_targetObject			= nullptr;				// target

private:
	float				_cameraMoveDistance		= 0.f;					// �������� ����
	float				_cameraFollowSpeed		= 500.f;				// ī�޶� fllow speed
	float				_cameraFollowTime		= 0.5f;					// ī�޶� ���󰡾��ϴ� �ð�
	float				_cameraEffectAccTime	= 0.f;					// ī�޶� ���� �ð�
	int32				_alphaValue				= 0;
	
	// ��� �(�����ؾ���)
private:
	// v = v0 - at
	float				_v0		= 50.f;									// ó�� �ӵ�
	float				_a		= 0.f;									// ���ӵ�
	float				_curSpeed = 0.f;								// ���� �ӵ�

	// Mouse LBTN
private:
	bool				_triggerLBTN = false;


	// Camera Effect	
private:
	CameraEffectInfo		_cameraEffectInfo	= {};
	queue<CameraEffectInfo> _cameraEffectQueue;

	CAMERA_EFFECT			_curCamEffect		= CAMERA_EFFECT::NONE;		// ���� ī�޶� ȿ��
	float					_curCamDuration		= 0.f;						// ���� ī�޶� ȿ�� ���ӽð�
	float					_curCamAccTime		= 0.f;						// ���� ī�޶� ȿ�� ������ ���� �ð�
	Texture*				_cameraTexture		= nullptr;					// ī�޶� �ؽ��� (���ҽ� �Ŵ����� ���� ���� �ؽ���)
	float					_curCamEffectRatio	= 0.f;						// ���� ī�޶� �ð��� ���� ���� ������
	bool					_nowCameraEffecting	= false;					// ���� ȿ���� ����������
};

