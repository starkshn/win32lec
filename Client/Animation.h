#pragma once

#include "Component.h"
#include "ChildComponent.h"

class Texture;

// �ִϸ��̼� �� ������ ���� ����
typedef struct AnimFrame
{
	Vec2 _leftTop;		// �»�� ��ġ
	Vec2 _animInterval; // �߷��� �ϴ� ũ��
	float _duration;    // �����Ӵ� �ӹ��� �ð�

} FrameInfo;


class Animation : public ChildComponent
{
public:
	Animation();
	virtual ~Animation() override;

public:
	virtual void Update() override;
	virtual void Render() override;
	virtual void Init() override;

	void CreateAnimation(Texture* pTex, Vec2 leftTopPos, Vec2 animInterval, Vec2 stepSize, float duration, uint32 iFrameCount);

private:
	void SetLoopAnimationAtFrame(uint32 frame);
	void UpdateAnimationFrame();

private:
	void SetAnimName(const wstring& name) { _animName = name; }
	friend class Animator;
public:
	wstring GetAnimName() { return _animName; }

	void SetLeftTopPos(Vec2 pos) { _leftTopPos = pos; }
	Vec2 GetLeftTopPos() { return _leftTopPos; }

	Vec2 GetInterval() { return _animInterval; }
	void SetAnimInterval(Vec2 interval) { _animInterval = interval; }

	Vec2 GetAnimStepSize() { return _animStepSize; }
	void SetAnimStepSize(Vec2 stepSize) { _animStepSize = stepSize; }

	uint32 GetAnimFrameCount() { return _frameCount; }
	void SetAnimFrameCount(uint32 frameCount) { _frameCount = frameCount; }

	const bool GetAnimLoop() { return _animLoop; }
	void SetAnimLoop(bool loop) { _animLoop = loop; }

	const bool GetAnimEnd() { return _animEnd; }
	void SetAnimEnd(bool end) { _animEnd = end; }

private:
	Texture* _animTexture	= nullptr;
	wstring _animName		= L"";
	Vec2	_leftTopPos		= {0.f, 0.f}; // �»��
	Vec2	_animInterval	= {0.f, 0.f}; // �ִϸ��̼� ����
	Vec2	_animStepSize	= {0.f, 0.f}; // ���� �ִϸ��̼Ǳ��� �Ÿ�
	float	_animDuration	= 0.f;
	uint32	_frameCount		= 0;
	vector<FrameInfo> _vecFrameInfo;

	uint32 _curFrame = 0; // ���� ������
	float _accTime = 0.f; // �ð��� ������ ����
	bool _animLoop = false; // ��ü �������� ���Ƽ� �ִϸ��̼� ����� �����ٴ� ���� �˸��� ��� ����
	bool _animEnd = false;
};

