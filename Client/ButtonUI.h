#pragma once
#include "UI.h"
class ButtonUI : public UI
{
public:
	ButtonUI();
	ButtonUI(const ButtonUI& origin);
	virtual ~ButtonUI() override;
	virtual ButtonUI* Clone() override;

public:
	// Mouse EVENT
	virtual void EVENT_MOUSE_HOVERON_UI() override;
	virtual void EVENT_MOUSE_LBTN_DOWN_UI() override;
	virtual void EVENT_MOUSE_LBTN_UP_UI() override;
	virtual void EVENT_MOUSE_LBTN_CLICK_UI() override;

private:

};

