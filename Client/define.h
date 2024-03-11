#pragma once

// make singleton instance (manager 클래스 생성후 선언)
#define DECLARE_SINGLE(classname)			\
private:									\
	classname();							\
	~classname();							\
public:										\
	static classname* GetInstance()			\
	{										\
		static classname s_instance;		\
		return &s_instance;					\
	}										\

// get single instance
#define GET_SINGLE(classname)	classname::GetInstance()

// Core
#define GET_WINDOW_HANDLE() GET_SINGLE(Core)->GetHwnd()
#define GET_MEMDC() GET_SINGLE(Core)->GetMemDC()

// Time
// delta time(double)
#define DT		GET_SINGLE(TimeManager)->GetDeltaTime()
// deltat time(float)
#define DT_F	GET_SINGLE(TimeManager)->GetDeltaTimeFloat()
// fps (UINT)
#define FPS		GET_SINGLE(TimeManager)->GetFPS()

// Key
// get key state
#define GET_KEY_STATE(k) GET_SINGLE(KeyManager)->GetKeyState(k)

enum class OBJECT_TYPE
{
	DEFAULT,
	RECTANGLE,
	PLAYER,
	MONSTER,
	PROJECTILE,

	LAST = 100,
	END = 101,
};

enum class SCENE_TYPE
{
	MAIN_MENU,
	START,
	STAGE_01,
	STAGE_02,

	TOOL = 99,
	LAST = 100,
	END = 101,
};

#define MAX_LENGH (uint32)OBJECT_TYPE::END

// std
#include <memory>
#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <string>
using namespace std;

// window
#include <Windows.h>
#include <windows.h>

// user's
#include "Core.h"
#include "struct.h"
#include "Types.h"

// Manager
#include "Manager.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "SceneManager.h"



