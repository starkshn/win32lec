#pragma once

// std
#include <memory>
#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <string>
using namespace std;

// window
#include <Windows.h>
#include <windows.h>
#include <assert.h>
#include <optional>
#include <tchar.h>

// header
#include "types.h"
#include "define.h"
#include "enums.h"

// Core
#include "Core.h"
#include "Camera.h"

// Manager
#include "Manager.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "PathManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
// #include "Camera.h" // <- 여기 선언하면 안된다.


// Utils
#include "SelectGDI.h"
#include "Func.h"
#include "WMath.h"


// lib
#pragma comment(lib, "Msimg32.lib")