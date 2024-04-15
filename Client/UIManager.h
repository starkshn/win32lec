#pragma once
#include "Manager.h"

class UI;

class UIManager : public Manager
{
public:
	DECLARE_SINGLE(UIManager);

public:
	void Init() override;
	void Update() override;

private:
	// OuterUI내에서 실제로 타겟팅 된 UI를 찾아서 반환한다.
	UI* GetTargetUI(UI* outerUI);
};

