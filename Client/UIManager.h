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

public:
	UI*		GetFocusingUI() { return _focusUI; }
	void	SetFocusingUI(UI* ui) { _focusUI = ui; }
	void	SetForceFocusingUI(UI* outerUI);

private:
	// OuterUI������ ������ Ÿ���� �� UI�� ã�Ƽ� ��ȯ�Ѵ�.
	UI* GetTargetUI(UI* outerUI);
	UI* FindFocusingUI();
	
private:
	UI* _focusUI = nullptr;
};

