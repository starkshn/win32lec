#pragma once
#include "Component.h"
#include "Animation.h"

class Texture;

// ���� ����Ÿ �̹��� �������� ���� 120px, ���� 130px

// Animation Ŭ���� �����ϴ� Ŭ����
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
	// ���� ��� �ؽ��� ���� pos: 0, 520
	// �� �ִϸ��̼Ǵ� �ڸ� ���� 120, 130 interval
	// anim �� ������(�̵��ϸ� �ڸ�) �Ÿ� 120, 0 stepSize
	// 1frame ���ӽð� duration 
	// 10 Frame
	// anim �̸�, texture ������, �»��, �ִϸ��̼� �� ����, �ڸ� ������(����), �����Ӵ� �ð�, ������ ī��Ʈ
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
	Animation* _curAnimation = nullptr; // ���� ������� �ִϸ��̼�
};

