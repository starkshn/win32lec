#pragma once
#include "Component.h"
#include "Animation.h"

class Texture;

// 젤다 마젠타 이미지 기준으로 가로 120px, 세로 130px

// Animation 클래스 관리하는 클래스
class Animator : public Component
{
public:
	Animator();
	virtual ~Animator() override;

public:
	virtual void Update() override;
	virtual void Render() override;
	virtual void Init() override;

public:
	// 120 x 130 
	// 정면 모습 텍스쳐 기준 pos: 0, 520
	// 한 애니매이션당 자를 간격 120, 130 interval
	// anim 간 스텝할(이동하며 자를) 거리 120, 0 stepSize
	// 1frame 지속시간 duration 
	// 10 Frame
	// anim 이름, texture 포인터, 좌상단, 애니매이션 간 간격, 자를 사이즈(스텝), 프레임당 시간, 프레임 카운트
	void CreateAnimation(const wstring& strAnimName, Texture* pTex, Vec2 leftTopPos, Vec2 animInterval, Vec2 stepSize, float duration, uint32 iFrameCount);
	Animation* FindAnimation(const wstring& animName);
	void PlayAnimation(const wstring& animName);

public:
	Animation* GetAnim() { return _curAnimation; }
	void SetAnim(Animation* pAnim) { _curAnimation = pAnim; }

	Animation* GetCurrentAnim() { return _curAnimation; }
	void SetCurrentAnim(Animation* pAnim)
	{
		_curAnimation = pAnim;
	}

private:
	map<wstring, Animation*> _mapAnims;
	Animation* _curAnimation = nullptr; // 현재 재생중인 애니매이션
};

