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
	virtual void Render() override;

public:
	// Mouse EVENT
	virtual void EVENT_MOUSE_HOVERON_UI() override;
	virtual void EVENT_MOUSE_LBTN_DOWN_UI() override;
	virtual void EVENT_MOUSE_LBTN_UP_UI() override;
	virtual void EVENT_MOUSE_LBTN_CLICK_UI() override;
	
public:
	void SetClickFunc(BTN_FUNC func, DWORD_PTR lparam, DWORD_PTR rparam) { _func = func; }

	void SetClickFunc(Object* object, OBJECT_MEM_FUNC memFunc) 
	{ 
		NULL_PTR_CHECK(object); NULL_PTR_CHECK(memFunc);
		_objectWhoCallMemFunc = object;
		_objectMemFunc = memFunc;
	}

	void SetClickFunc(Scene* scene, SCENE_MEM_FUNC memFunc)
	{
		NULL_PTR_CHECK(scene); NULL_PTR_CHECK(memFunc);
		_sceneWhoCallMemFunc = scene;
		_sceneMemFunc = memFunc;
	}

public:
	wstring GetButtonText() { return _text; }
	void SetButtonText(wstring text) { _text = text; }

protected:
	Object* _objectWhoCallMemFunc	= nullptr;
	OBJECT_MEM_FUNC	_objectMemFunc	= nullptr;

	Scene* _sceneWhoCallMemFunc		= nullptr;
	SCENE_MEM_FUNC	_sceneMemFunc	= nullptr;

	BTN_FUNC		_func			= nullptr;
	DWORD_PTR		_lparam			= 0;
	DWORD_PTR		_rparam			= 0;
	wstring			_text			= L"";
};

