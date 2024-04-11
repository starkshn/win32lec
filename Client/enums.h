#pragma once

enum class OBJECT_TYPE
{
	DEFAULT,
	RECTANGLE,
	PLAYER,
	MONSTER,
	PROJ_PLAYER,
	PROJ_MONSTER,
	PROJECTILE_LINE,
	BRICK,
	DEFAULT_TILE,

	UI,

	END = MAX_LENGH,
};

enum class SCENE_TYPE
{
	MAIN_MENU,
	START,
	STAGE_01,
	STAGE_02,

	TOOL = 31,

	END = MAX_LENGH,
};

enum class RESOURCE_TYPE
{
	NONE,
	TEXTURE,
	SOUND,

	END = MAX_LENGH,
};

enum class FILE_TYPE
{
	NONE,
	BITMAP,
	PNG,
	JPG,


	END = MAX_LENGH,
};

enum class BRUSH_TYPE
{
	HOLLOW,


	END = MAX_LENGH,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,


	END = MAX_LENGH,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	

	END = MAX_LENGH,
};

enum class COMP_TYPE
{
	COLLIDER = 1,
	ANIMATOR = 2,
	MOVEMENT = 3,

	END = MAX_LENGH,
};