#pragma once
#include "define.h"

//enum class VK
//{
//	VK_LEFT,
//	VK_DOWN,
//	VK_RIGHT,
//	VK_UP,
//	'Q',
//	'E',
//	'R',
//	'T',
//	'Y',
//	'U',
//	'I',
//	'O',
//	'P',
//	'W',
//	'A',
//	'S',
//	'D',
//	VK_MENU,
//	VK_LSHIFT,
//	VK_CONTROL,
//	VK_SPACE,
//	VK_RETURN,
//	VK_ESCAPE,
//
//	// LAST = 100,
//};


enum class KEY_STATE
{
	NONE,
	PRESSED,
	HOLD,
	RELEASED,
};

enum class KEY
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
class KeyManager : public Manager
{
	DECLARE_SINGLE(KeyManager);

public:
	virtual void Init() override;
	virtual void Update() override;

public:
	KEY_STATE GetKeyState(KEY key) { return _keys[int(key)]._keyState; }
	
private:
	vector<KeyInfo> _keys;
	int VK_Mapping[(int)KEY::LAST];
};

