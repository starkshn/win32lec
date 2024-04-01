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

	END = 32,
};

enum class SCENE_TYPE
{
	MAIN_MENU,
	START,
	STAGE_01,
	STAGE_02,

	TOOL = 31,



	END = 32,
};

enum class RESOURCE_TYPE
{
	NONE,
	TEXTURE,
	SOUND,


	END,
};

enum class FILE_TYPE
{
	NONE,
	BITMAP,
	PNG,
	JPG,


	END,
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

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	

	END,
};

enum class COMP_TYPE
{
	COLLIDER = 1,
	ANIMATOR = 2,
	MOVEMENT = 3,

	END = 32,
};