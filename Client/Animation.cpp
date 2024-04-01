#include "pch.h"
#include "Animation.h"
#include "Texture.h"


Animation::Animation()
{

}

Animation::~Animation()
{

}

void Animation::Update()
{
	// FinalPos (Player ��ġ) ������Ʈ
	Component::Update();

	// ���� �ִϸ��̼��� ���� �����Ѱ��
	if (GetAnimEnd())
	{
		// ���� �ִϸ��̼��̶�� �ʱ�ȭ �� ����Ѵ�.
		if (GetAnimLoop())
		{
			// �ִϸ��̼� ������ 0���� �ʱ�ȭ
			SetLoopAnimationAtFrame(0);
			SetAnimEnd(false);
			UpdateAnimationFrame();
		}
	}
	// �ִϸ��̼��� ���� ������ ��찡 �ƴѰ�� �״�� ���
	// ���� �ִϸ��̼��̵� �ƴ� �ִϸ��̼��̵� �ϴ� 
	// ������ ������Ʈ ȣ�� ���ش�.
	else
	{
		UpdateAnimationFrame();
	}
}

void Animation::Render()
{
	// �ִϸ��̼� ������ Ȯ�� 
	// ���� �����ߴµ� ������ �ƴѰ�� return 
	if (GetAnimEnd() && GetAnimLoop() == false) return;
	if (_curFrame == -1) return;

	Vec2 fp = GetFinalPos();
	Vec2 interval = _vecFrameInfo[_curFrame]._animInterval;
	Vec2 ltp = _vecFrameInfo[_curFrame]._leftTop;

	TransparentBlt
	(
		GET_MEMDC, 
		(int)(fp.x - interval.x / 2),
		(int)(fp.y - interval.y / 2),
		int(interval.x), int(interval.y),
		_animTexture->GetDC(),
		int(ltp.x), int(ltp.y),
		int(interval.x), int(interval.y),
		RGB(255, 0, 255)
	);
}

void Animation::Init()
{

}

void Animation::CreateAnimation(Texture* pTex, Vec2 leftTopPos, Vec2 animInterval, Vec2 stepSize, float duration, uint32 iFrameCount)
{
	_animTexture = pTex;
	
	FrameInfo frinfo = {};
	// �� �ִϸ��̼� �� �������� �ִϸ��̼� ������ ����
	for (uint32 i = 0; i < iFrameCount; i++)
	{
		frinfo._duration = duration;
		frinfo._animInterval = animInterval;
		frinfo._leftTop = leftTopPos + (float(i) * stepSize);

		_vecFrameInfo.push_back(frinfo);
	}
}

void Animation::SetLoopAnimationAtFrame(uint32 frame)
{
	// �������� ������ ������� �ƴ��� Ȯ��
	if (frame < 0 || frame >= _vecFrameInfo.size())
	{
		assert(1);
	}
	
	// temp : Player Ŭ��������
	// ���鶧 ���� ���� �ִϸ��̼��� �ƴѰ�� �״�� return 
	if (GetAnimLoop() == false) return;

	// �ʱ�ȭ
	_accTime = 0.f;
	_curFrame = 0;
}

void Animation::UpdateAnimationFrame()
{
	if (_curFrame == -1) return;

	_accTime += DT_F;

	if (_accTime >= _vecFrameInfo[_curFrame]._duration)
	{
		++_curFrame;
		if (_vecFrameInfo.size() <= _curFrame)
		{
			SetAnimEnd(true);
			_curFrame = -1;
		}

		_accTime = _accTime - _vecFrameInfo[_curFrame]._duration;
	}
}
