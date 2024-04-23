#pragma once
#include "Object.h"

class UI : public Object
{
public:
	UI();
	virtual ~UI() override;
	UI(const UI& origin);
	virtual UI* Clone() override;

public:
	virtual void Update() override;
	virtual void FinalUpdate() override;
	virtual void Render() override;
	virtual void Init() override;
	virtual void Begin() override;
	virtual void End() override;

public:
	void UpdateInnerUI();
	void RenderInnerUI();
	void FinalUpdateInnerUI();

	// FinalUpdate시점에서 마우스가 현재 위에 있는지 여부
	virtual void UpdateMouseInteraction() override;

public:
	// Mouse EVENT
	virtual void EVENT_MOUSE_HOVERON_UI();
	virtual void EVENT_MOUSE_LBTN_DOWN_UI();
	virtual void EVENT_MOUSE_LBTN_UP_UI();
	virtual void EVENT_MOUSE_LBTN_CLICK_UI();

public:
	void AddInnerUI(UI* innerUI) { _vecInnerUI.push_back(innerUI); }

public:
	vector<UI*>& GetInnerUI() { return _vecInnerUI; }
	void SetInnerUI(UI* innerUI)
	{
		if (nullptr != innerUI)
		{
			_vecInnerUI.push_back(innerUI);
			innerUI->SetOuterUI(this);
			Vec2 outerUIPos = GetPos();
			innerUI->SetPos(outerUIPos + innerUI->GetUIOffSet());
		}
		else assert(nullptr);
	}

	UI* GetOuterUI() 
	{
		if (nullptr != _outerUI) return _outerUI; 
		return nullptr;
	}
	void SetOuterUI(UI* outerUI) { _outerUI = outerUI; }

	Vec2 GetUIOffSet() { return _offset; }
	void SetUIOffSet(Vec2 offset) { _offset = offset; }
	
	Vec2 GetUIFinalPos() { return _finalPos; }
	void SetUIFinalPos(Vec2 pos) { _finalPos = pos; }

	// Affected By Camera
	bool GetThisUIAffectByCamera() { return _affectByCameraPos; }
	void SetThisUIAffectByCamera(bool abc) { _affectByCameraPos = abc; }


	// UI <-> Mouse
public:
	// Object로 부터 상속받은 함수
	virtual bool GetMouseHoverOnThisObject() override;
	virtual void SetMouseHoverOnThisObject(bool hoverOn) override;

	bool GetMouseHoverOnThisUI() { return _mouseHoverOn; }
	void SetMouseHoverOnThisUI(bool hover) { _mouseHoverOn = hover; }

	bool GetLBTNDownOnThisUI() { return _lbtnDownOnThisUI; }
	void SetLBTNDownOnThisUI(bool lbtnDown) { _lbtnDownOnThisUI = lbtnDown; }

	bool GetVisible() { return _visible; }
	void SetVisible(bool visible);

private:
	void SetOuterVisible(bool visible);
	void SetInnerVisible(bool visible);
	UI* GetRootUI();
	
private:
	vector<UI*> _vecInnerUI;
	UI*			_outerUI			= nullptr;
	Vec2		_offset				= Vec2(0, 0);
	Vec2		_finalPos			= Vec2(0, 0);
	bool		_affectByCameraPos	= false;
	bool		_mouseHoverOn		= false; // 현재 UI위에 마우스가 있는지

	// 현재 UI에서 lbtn이 down되었는지에 대한 여부
	bool		_lbtnDownOnThisUI	= false;
	bool		_visible			= true;
	
	friend class UIManager;
};

