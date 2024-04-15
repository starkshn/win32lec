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
	// OuterUI������ ������ Ÿ���� �� UI�� ã�Ƽ� ��ȯ�Ѵ�.
	UI* GetTargetUI(UI* outerUI);
};

