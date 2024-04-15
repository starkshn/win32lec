#pragma once

// forward declarations...
// class Command;

enum class KEY_STATE
{
	NONE,
	PRESSED,
	HOLD,
	RELEASED,
};

enum class KEYES
{
	LEFT,
	DOWN,
	RIGHT,
	UP,
	Q,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	W,
	A,
	S,
	D,
	ALT,
	LSHIFT,
	CTRL,
	SPACE,
	ENTER,
	ESC,
	LBTN,
	RBTN,

	LAST = 100,
};

struct KeyInfo
{
	KEY_STATE	_keyState;
	bool		_prevPressedState;		// 이전 프레임에서 state
};

// for what?
// 1. frame sync
// 2. key mapping
// 3. InputHandler 역할
class KeyManager : public Manager
{
	DECLARE_SINGLE(KeyManager);

public:
	virtual void Init() override;
	virtual void Update() override;

public:
	KEY_STATE GetKeyState(KEYES key) { return _keys[int(key)]._keyState; }

	void UpdateKeyInput();
	void UpdateMousePos();
	void UpdateMouseWheel(int16 upDownValue);

	// 현재 윈도우 기준 렌더링 좌표를 반환
	Vec2 GetMousePos() { return _curMousePos; }
	void SetMousePos(Vec2 pos) { _curMousePos = pos; }
	
private:
	vector<KeyInfo> _keys;
	int VK_Mapping[(int)KEYES::LAST];
	Vec2 _curMousePos;
	
};

