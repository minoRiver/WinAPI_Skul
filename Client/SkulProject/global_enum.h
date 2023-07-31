#pragma once

enum class GroupType
{
	Default,
	Player,
	Missile,
	Monster,

	UI = 31,
	End = 32,
};

enum class SceneType
{
	Tool,
	Start,

	End,
};

enum class BrushType
{
	Hollow,
	End,
};

enum class PenType
{
	Red,
	Green,
	Blue,
	End,
};