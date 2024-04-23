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

// pch.h�� �Ƹ� �־ �Ǵ� ���ϴ� ��� ���� �ؾ���...??
// ���漱������ �ذ��� �ȵȴ� -> ���ε��� �ؾ��ϱ� ������ Ŭ������ ���� ������ �� �Ѱ��־���Ѵ�.
// #include "Scene.h"
// #include "Object.h"

class Object;
class Scene;

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

// Object ��� �Լ� ������
typedef void (Object::* OBJECT_MEM_FUNC)(void);

// Scene ����Լ� ������
typedef void (Scene::* SCENE_MEM_FUNC)(void);