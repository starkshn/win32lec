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

// Get single instance
#define GET_SINGLE(classname)	classname::GetInstance()

// 0 ~ 100
#define MAX_LENGH (uint32)OBJECT_TYPE::END

// Get Manager
#define TIME	GET_SINGLE(TimeManager)
#define KEY		GET_SINGLE(KeyManager)
#define SCENE	GET_SINGLE(SceneManager)
#define CORE	GET_SINGLE(Core)


// Core
#define GET_WINDOW_HANDLE() CORE->GetHwnd()
#define GET_MEMDC()			CORE->GetMemDC()
#define GET_RESOLUTION()	CORE->GetResolution()

// Time Manager
#define DT		TIME->GetDeltaTime() // delta time(double)
#define DT_F	TIME->GetDeltaTimeFloat() // deltat time(float)
#define FPS		TIME->GetFPS() // fps (UINT)

// Key Manager
#define GET_KEY_STATE(k) KEY->GetKeyState(k) // get key state
#define KEY_CMP(key, state) GET_KEY_STATE(key) == state
#define KEY_HOLD(key) KEY_CMP(key, KEY_STATE::HOLD)
#define KEY_PRESSED(key) KEY_CMP(key, KEY_STATE::PRESSED)
#define KEY_RELEASED(key) KEY_CMP(key, KEY_STATE::RELEASED)


// Object
#define DEFAULT_X_SCALE 50.f
#define DEFAULT_Y_SCALE 50.f
#define DEFAULT_SCALE Vec2(DEFAULT_X_SCALE, DEFAULT_Y_SCALE)
#define DEFAULT_OBJECT_TYPE OBJECT_TYPE::RECTANGLE
#define DEFAULT_OBJECT_STATE OBJECT_STATE::DEFAULT
#define DEFAULT_PATROL_TYPE PATROL_TYPE::NONE
#define DEFAULT_ROTATE_TYPE ROTATE_TYPE::CIRCLE
#define DEFAULT_PROPERTY_TYPE OBJECT_PROPERTY::STATIC
#define DEFAULT_SPEED 50.f
#define DEFAULT_PATROL_DISTANCE 100.f
#define DEFAULT_DIR Vec2(1, 0)
#define GET_PLAYER() SCENE->GetPlayer()

	// Render
#define DRAW_RECT() Rectangle(GET_MEMDC(), this->GetLeft(), this->GetTop(), this->GetRight(), this->GetBottom());
#define DRAW_CIRCLE() Ellipse(GET_MEMDC(), this->GetLeft(), this->GetTop(), this->GetRight(), this->GetBottom());
// #define DRAW_LINE(start, end) LineTo(GET_MEMDC(), start, end) 

	// projectile
#define DEFAULT_PROJ_SCALE Vec2(30.f, 30.f)
#define DEFAULT_PROJ_SPEED 300.f
#define OBJ_PROJECTILE OBJECT_TYPE::PROJECTILE
#define DEFAULT_PROJECTILE_POS Vec2(this->GetPos().x, this->GetPos().y - this->GetScale().y / 2 - DEFAULT_PROJ_SCALE.y / 2)

	// angle
#define CHECK_SIN_ANGLE(angle)							\
if(angle > 360.f)									\
{													\
	this->SetAngle(angle - 360.f);					\
	this->SetAngle(0.f);							\
}													\

// math
#define PI 3.141592
#define RAD(angle) angle * PI / 180
#define ANGLE(rad) rad * 180 / PI




