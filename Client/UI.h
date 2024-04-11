#pragma once
#include "Object.h"
class UI : public Object
{
public:
	UI();
	~UI() override;
	Object* Clone() override;

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

public:
	void AddInnerUI(UI* innerUI) { _vecInnerUI.push_back(innerUI); }

public:
	vector<UI*>& GetInnerUI() { return _vecInnerUI; }
	void SetInnerUI(UI* innerUI)
	{
		if (nullptr != innerUI)
			_vecInnerUI.push_back(innerUI);
		else assert(nullptr);
	}

	UI* GetOuterUI() { return _outerUI; }
	void SetOuterUI(UI* outerUI) { _outerUI = outerUI; }

	Vec2 GetUIOffSet() { return _offset; }
	void SetUIOffSet(Vec2 offset) { _offset = offset; }
	
	Vec2 GetUIFinalPos() { return _finalPos; }
	void SetUIFinalPos(Vec2 pos) { _finalPos = pos; }

private:
	vector<UI*> _vecInnerUI;
	UI*			_outerUI	= nullptr;
	Vec2		_offset		= Vec2(0, 0);
	Vec2		_finalPos	= Vec2(0, 0);
};

