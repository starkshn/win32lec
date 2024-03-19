#pragma once

enum class OBJECT_TYPE
{
	DEFAULT,
	RECTANGLE,
	PLAYER,
	MONSTER,
	PROJECTILE,
	PROJECTILE_LINE,
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

enum class RESOURCE_TYPE
{
	NONE,
	TEXTURE,
	SOUND,
};

enum class FILE_TYPE
{
	NONE,
	BITMAP,
	PNG,
	JPG,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};