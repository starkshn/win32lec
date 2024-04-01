#include "pch.h"
#include "Animator.h"
#include "Animation.h"
#include "Texture.h"

Animator::Animator()
{
}

Animator::~Animator()
{
	DeleteResourcesSafe(_mapAnims);
}

void Animator::Update()
{
	Animation* curAnim = GetAnim();
	if (nullptr != curAnim)
	{
		GetAnim()->Update();
	}
}

void Animator::Render()
{
	Animation* curAnim = GetAnim();
	if (nullptr != curAnim)
	{
		PlayAnimation(Z_WALK_FRONT);
	}
}

void Animator::Init()
{

}

void Animator::CreateAnimation(const wstring& strAnimName, Texture* pTex, Vec2 leftTopPos, Vec2 animInterval, Vec2 stepSize, float duration, uint32 iFrameCount)
{
	Animation* newAnim = FindAnimation(strAnimName);

	// ���� �̸��� �ִϸ��̼��� �ִٸ� assert
	assert(nullptr == newAnim);
	
	newAnim = new Animation;
	newAnim->SetOwnerComp(this);
	newAnim->SetAnimName(strAnimName);
	newAnim->SetLeftTopPos(leftTopPos);
	newAnim->SetAnimInterval(animInterval);
	newAnim->SetAnimStepSize(stepSize);
	newAnim->SetAnimFrameCount(iFrameCount);
	newAnim->CreateAnimation(pTex, leftTopPos, animInterval, stepSize, duration, iFrameCount);

	_mapAnims.insert(make_pair(newAnim->GetAnimName(), newAnim));

	// Player�ʿ��� ���� CreateComponent�� ȣ���� �Լ��� �ƴϱ⶧���� OuterObject������ �������ش�
	static_cast<Component*>(newAnim)->SetOwnerObject(this->GetOwnerObject());
}

Animation* Animator::FindAnimation(const wstring& animName)
{
	auto iter = _mapAnims.find(animName);
	if (iter == _mapAnims.end())
		return nullptr;
	else
		return iter->second;
}


void Animator::PlayAnimation(const wstring& animName)
{
	_curAnimation = FindAnimation(animName);
	_curAnimation->Render();
}
