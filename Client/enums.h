#pragma once

enum class OBJECT_TYPE
{
	DEFAULT,
	RECTANGLE,
	PLAYER,
	MONSTER,
	PROJECTILE,
	BRICK,

	LAST = 100,
	END = 101,
};

enum class OBJECT_STATE
{
	DEFAULT,
	PATROL,
	ROTATE,
};

enum class PATROL_TYPE
{
	NONE,
	VERTICAL = 1,
	HORIZON  = 2,
};

enum class ROTATE_TYPE
{
	NONE,
	CIRCLE,
	
};

enum class OBJECT_PROPERTY
{
	NONE,
	STATIC,
	DYNAMIC,
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
