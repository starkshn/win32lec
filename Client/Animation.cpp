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
	// FinalPos (Player 위치) 업데이트
	Component::Update();

	// 현재 애니매이션이 끝에 도달한경우
	if (GetAnimEnd())
	{
		// 루프 애니매이션이라면 초기화 후 재생한다.
		if (GetIsLoopAnimation())
		{
			// 애니매이션 프레임 0으로 초기화
			SetLoopAnimationAtFrame(0);
			SetAnimEnd(false);
			UpdateAnimationFrame();
		}
	}
	// 애니매이션이 끝에 도달한 경우가 아닌경우 그대로 재생
	// 루프 애니매이션이든 아닌 애니매이션이든 일단 
	// 프레임 업데이트 호출 해준다.
	else
	{
		UpdateAnimationFrame();
	}
}

void Animation::Render()
{
	Component::Render();

	// 애니매이션 끝도달 확인
	// 끝에 도달했는데 루프가 아닌경우 종료 
	if (GetAnimEnd() && GetIsLoopAnimation() == false) return;
	
	Vec2 renderPos = GetRenderPos();
	Vec2 interval = _vecFrameInfo[_curFrame]._animInterval;
	Vec2 ltp = _vecFrameInfo[_curFrame]._leftTop;
	Vec2 offset = _vecFrameInfo[_curFrame]._offset;

	TransparentBlt
	(
		GET_MEMDC, 
		(int)((renderPos.x + offset.x) - interval.x / 2),
		(int)((renderPos.y + offset.y) - interval.y / 2),
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
	// 한 애니매이션 당 만들어야할 애니매이션 프레임 개수
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
	// 프레임이 범위를 벗어나는지 아닌지 확인
	if (frame < 0 || frame >= _vecFrameInfo.size())
	{
		assert(1);
	}
	
	// temp : Player 클래스에서
	// 만들때 부터 루프 애니매이션이 아닌경우 그대로 return 
	if (GetIsLoopAnimation() == false) return;

	// 초기화
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
			// 애니매이션이 끝났다면 이전 프레임 애니매이션 프레임 인덱스로 설정해준다.
			_curFrame = uint32(_vecFrameInfo.size() - 1);
			_accTime = 0.f;
			return;
		}

		_accTime = _accTime - _vecFrameInfo[_curFrame]._duration;
	}
}
