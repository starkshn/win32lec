#pragma once
#include "UI.h"

class PanelUI : public UI
{
public:
	PanelUI();
	PanelUI(const PanelUI& origin);
	virtual ~PanelUI() override;
	virtual PanelUI* Clone() override;

public:
	virtual void Update() override;
	virtual void FinalUpdate() override;
	virtual void Render() override;
	virtual void Init() override;
	virtual void Begin() override;
	virtual void End() override;


public:
	// Mouse EVENT
	virtual void EVENT_MOUSE_HOVERON_UI() override;
	virtual void EVENT_MOUSE_LBTN_DOWN_UI() override;
	virtual void EVENT_MOUSE_LBTN_UP_UI() override;
	virtual void EVENT_MOUSE_LBTN_CLICK_UI() override;

public:
	bool GetCanDrag() { return _canDrag; }
	void SetCanDrag(bool drag) { _canDrag = drag; }

private:
	Vec2 _dragStartPos	= Vec2(0.f, 0.f);
	bool _canDrag		= true;
};

