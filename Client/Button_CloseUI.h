#pragma once
#include "ButtonUI.h"

class Button_CloseUI : public ButtonUI
{
public:
	Button_CloseUI();
	Button_CloseUI(const Button_CloseUI& origin);
	virtual ~Button_CloseUI() override;
	virtual Button_CloseUI* Clone() override;

public:
	void CloseThisUI();
};

