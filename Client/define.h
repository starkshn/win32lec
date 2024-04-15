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
											\

// Get single instance
#define GET_SINGLE(classname)	classname::GetInstance()

// Get Manager
#define TIME		GET_SINGLE(TimeManager)
#define KEY			GET_SINGLE(KeyManager)
#define SCENE		GET_SINGLE(SceneManager)
#define PATH		GET_SINGLE(PathManager)
#define RESOURCE	GET_SINGLE(ResourceManager)
#define COLLISION	GET_SINGLE(CollisionManager)
#define EVENT		GET_SINGLE(EventManager)
#define CORE		GET_SINGLE(Core)
#define GDI			GET_SINGLE(SelectGDI)
#define CAMERA		GET_SINGLE(Camera)
#define UI_MANAGER	GET_SINGLE(UIManager)
#define BOARD		GET_SINGLE(BoardManager)

// 0 ~ 100
#define MAX_LENGH 32

// Get Core
#define GET_MAIN_DC			CORE->GetMainDC()
#define GET_WINDOW_HANDLE	CORE->GetHwnd()
#define GET_MEMDC			CORE->GetMemDC()
#define GET_RESOLUTION		CORE->GetResolution()


// Get Scene
#define GET_PLAYER			SCENE->GetPlayer()


// Get Key
#define GET_KEY_STATE(k) KEY->GetKeyState(k)


// Time Manager
#define DT		TIME->GetDeltaTime() // delta time(double)
#define DT_F	TIME->GetDeltaTimeFloat() // deltat time(float)
#define FPS		TIME->GetFPS() // fps (UINT)


// Key Manager
#define KEY_CMP(key, state) GET_KEY_STATE(key) == state
#define KEY_HOLD(key) KEY_CMP(key, KEY_STATE::HOLD)
#define KEY_PRESSED(key) KEY_CMP(key, KEY_STATE::PRESSED)
#define KEY_RELEASED(key) KEY_CMP(key, KEY_STATE::RELEASED)

// Mouse Pos
#define GET_MOUSE_POS KEY->GetMousePos() // <= 렌더링 좌표기준 마우스 좌표 반환
#define GET_WINDOW_MOUSE_POS(renderMousePos) CAMERA->GetWindowActualPosFromRenderPos(renderMousePos)
#define GET_RENDER_MOUSE_POS(windowMousePos) CAMERA->GetRenderPosFromWindowActualPos(windowMousePos)
#define WINDOW_MOUSE_POS CAMERA->GetWindowActualPosFromRenderPos(GET_MOUSE_POS)
#define RENDER_MOUSE_POS CAMERA->GetRenderPosFromWindowActualPos(WINDOW_MOUSE_POS)

// Resource
#define GET_C_PATH PATH->GetContentDirPath()
#define RES RESOURCE_TYPE 


// Object
#define DEFAULT_X_SCALE 50.f
#define DEFAULT_Y_SCALE 50.f
#define DEFAULT_SCALE Vec2(DEFAULT_X_SCALE, DEFAULT_Y_SCALE)
#define DEFAULT_OBJECT_TYPE OBJECT_TYPE::RECTANGLE
#define DEFAULT_SPEED 50.f
#define DEFAULT_PATROL_DISTANCE 100.f
#define DEFAULT_DIR Vec2(1, 0)


#define MAX_TILE_COUNT 9

// Render
#define DRAW_RECT() Rectangle(GET_MEMDC, this->GetLeft(), this->GetTop(), this->GetRight(), this->GetBottom());
#define DRAW_CIRCLE() Ellipse(GET_MEMDC, this->GetLeft(), this->GetTop(), this->GetRight(), this->GetBottom());
#define DRAW_RECT_COLLIDER(left, top, right, bottom) Rectangle(GET_MEMDC, left, top, right, bottom);

// projectile
#define DEFAULT_PROJ_SCALE Vec2(30.f, 30.f)
#define DEFAULT_PROJ_SPEED 300.f
#define OBJ_PROJECTILE OBJECT_TYPE::PROJ_PLAYER
#define DEFAULT_PROJECTILE_POS Vec2(this->GetPos().x, this->GetPos().y - this->GetScale().y / 2 - DEFAULT_PROJ_SCALE.y / 2)

// angle
#define CHECK_SIN_ANGLE(angle)						\
if(angle > 360.f)									\
{													\
	this->SetAngle(angle - 360.f);					\
	this->SetAngle(0.f);							\
}													\

// dir
#define DIR_UP		Vec2(0, 1)
#define DIR_DOWN	Vec2(0, -1)
#define DIR_LEFT	Vec2(-1, 0)
#define DIR_RIGHT	Vec2(1, 0)

// math
#define PI 3.141592
#define RAD(angle) angle * PI / 180
#define ANGLE(rad) rad * 180 / PI

// Animation Test
#define Z_WALK_FRONT L"Walk_Front"

// Tile
#define TILE_SIZE 64

// check nullptr
#define NULL_PTR_CHECK(ptr)		\
if (nullptr == ptr)				\
{								\
	assert(ptr);				\
}								\
								\
// check valid idx
#define IS_VALID_IDX(arr, idx) assert(arr.size() > idx)

