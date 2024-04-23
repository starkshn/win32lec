#pragma once
#include <windows.h>
#include "DirectXMath.h"
#include "SimpleMath.h"


using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64; // long long

using uint8 = unsigned	__int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

using Vec2 = DirectX::SimpleMath::Vector2;
using Vec3 = DirectX::SimpleMath::Vector3;
using Vec4 = DirectX::SimpleMath::Vector4;
using Matrix = DirectX::SimpleMath::Matrix;
using Quaternion = DirectX::SimpleMath::Quaternion;

// pch.h에 아마 있어서 되는 듯하다 헤더 포함 해야함...??
// 전방선언으로 해결이 안된다 -> 바인딩을 해야하기 때문에 클래스에 대한 정보를 다 넘겨주어야한다.
// #include "Scene.h"
// #include "Object.h"

class Object;
class Scene;

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

// Object 멤버 함수 포인터
typedef void (Object::* OBJECT_MEM_FUNC)(void);

// Scene 멤버함수 포인터
typedef void (Scene::* SCENE_MEM_FUNC)(void);