#pragma once
#include "UI.h"

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

class ButtonUI : public UI
{
public:
	ButtonUI();
	ButtonUI(const ButtonUI& origin);
	virtual ~ButtonUI() override;
	virtual ButtonUI* Clone() override;

public:
	virtual void Render() override;


public:
	// Mouse EVENT
	virtual void EVENT_MOUSE_HOVERON_UI() override;
	virtual void EVENT_MOUSE_LBTN_DOWN_UI() override;
	virtual void EVENT_MOUSE_LBTN_UP_UI() override;
	virtual void EVENT_MOUSE_LBTN_CLICK_UI() override;
	
public:
	void SetClickFunc(BTN_FUNC func, DWORD_PTR lparam, DWORD_PTR rparam) { _func = func; }

	wstring GetButtonText() { return _text; }
	void SetButtonText(wstring text) { _text = text; }

private:
	BTN_FUNC	_func		= nullptr;
	DWORD_PTR	_lparam;
	DWORD_PTR	_rparam;
	wstring		_text		= L"";
};

