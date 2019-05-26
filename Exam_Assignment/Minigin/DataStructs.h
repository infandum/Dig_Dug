#pragma once
#include "MiniginPCH.h"
#include <windows.h>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	enum class StatusCode
	{
		STATUS_SUCCES,
		STATUS_ERROR
	};

	enum class PlayerType
	{
		PLAYER_DIGDUG,
		PLAYER_FYGAR,
		PLAYER_NONE
	};
	enum class NPCType
	{
		ROCK,
		POOKA,
		FYGAR
	};

	enum NPCBasePoints : UINT
	{
		POINTS_POOKA = 200,
		POINTS_FYGAR = 400,
	};

	//2D VECTORS
	class fVector2
	{
	public:
		fVector2() = default;
		fVector2(float x, float y) :x(x), y(y) {}
		~fVector2() = default;

		float x;
		float y;

		bool IsNullVector() const;
		StatusCode Normalize();
		float Magnitude() const;
	};

	inline bool fVector2::IsNullVector() const
	{
		return x == 0.0f && y == 0.0f;
	}

	inline StatusCode fVector2::Normalize()
	{
		if (x == 0 && y == 0)
		{
			return StatusCode::STATUS_ERROR;
		}
		const auto magnitude = Magnitude();
		x /= magnitude;
		y /= magnitude;
		return StatusCode::STATUS_SUCCES;
	}

	inline float fVector2::Magnitude() const
	{
		return std::sqrt(x * x + y * y);
	}

	class iVector2
	{
	public:
		iVector2() = default;
		iVector2(int x, int y) :x(x), y(y) {}
		~iVector2() = default;

		int x;
		int y;

		bool IsNullVector() const;
		StatusCode Normalize();
		float Magnitude() const;
	};

	inline bool iVector2::IsNullVector() const
	{
		return x == 0 && y == 0;
	}

	inline StatusCode iVector2::Normalize()
	{
		if (x == 0 && y == 0)
		{
			return StatusCode::STATUS_ERROR;
		}
		const auto magnitude = Magnitude();
		x /= static_cast<int>(magnitude);
		y /= static_cast<int>(magnitude);
		return StatusCode::STATUS_SUCCES;
	}

	inline float iVector2::Magnitude() const
	{
		return static_cast<float>(std::sqrt(x * x + y * y));
	}
	

	enum class NotifyEvent
	{
		EVENT_INIT,
		EVENT_RESET,
		EVENT_SPAWN,
		EVENT_DESPAWN,
		EVENT_IDLE,
		EVENT_MOVE,
		EVENT_ACTION,
		EVENT_INTERACT,
		EVENT_CHARGE,
		EVENT_COLLISION,
		EVENT_CRUSHED,
		EVENT_LIFE_CHECK,
		EVENT_VALUE_CHECK,
		EVENT_GAME_OVER
	};

	enum class Direction
	{
		RIGHT = 0,
		LEFT = 1,
		UP = 2,
		DOWN = 3,
		NONE = 4

		
	};


	enum class TileState
	{
		FREE,
		USED,
		BLOCKED,
		OCCUPIED,
		EMPITY,
		TILESTATE_MAX_COUNT
	};

	enum class ControllerButton
	{
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,
		ButtonUp = 0x0001,
		ButtonDown = 0x0002,
		ButtonLeft = 0x0004,
		ButtonRight = 0x0008,
		ButtonStart = 0x0010,
		ButtonSelect = 0x0020,
		ButtonLeftThumb = 0x0040,
		ButtonRightThumb = 0x0080,
		ButtonLeftTrigger = 0x0100,
		ButtonRightTrigger = 0x0200,
		ButtonNone = 0x0000
	};

	inline glm::vec3 DirectionAxis(Direction dir)
	{
		switch (dir)
		{
		case Direction::RIGHT:
			return { 1,0,0 };
		case Direction::LEFT:
			return { -1,0,0 };
		case Direction::UP:
			return { 0, -1,0 };
		case Direction::DOWN:
			return { 0, 1,0 };

		case Direction::NONE:
			return { 0,0,0 };
		}
		return {};
	}

	inline Direction AxisDirection(glm::vec3 velocity)
	{
		Direction dir;
		if (velocity.x < 0.0f)
			dir = Direction::LEFT;
		else if (velocity.x > 0.0f)
			dir = Direction::RIGHT;
		else if (velocity.y < 0.0f)
			dir = Direction::UP;
		else if (velocity.y > 0.0f)
			dir = Direction::DOWN;
		else
			dir = Direction::NONE;

		return dir;
	}

	inline float RandomFloatBetween(float min = 0.f, float max = 1.f)
	{
		return  min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
	}

	inline int RandomIntBetween(int min = 0.f, int max = 1.f)
	{
		return min + static_cast<int>(rand() / (static_cast<int>(RAND_MAX / (max - min))));
	}
	struct AnimationClip
	{
		UINT id = 0;
		std::vector<std::vector<UINT>> TextureList;
		UINT frames = 1;
		bool hasUpDown = false;
		bool isLooping = false;
	};

	struct SpriteClip
	{
		UINT id = 0;
		std::string Name = "";
		iVector2 UV = { 0 , 0 };
		iVector2 Size = { 32 , 32 };
		UINT StartFrame = 0;
		UINT Frames = 1;
		bool HasUpDown = false;
		bool IsLooping = false;
		bool IsSingle = false;
		float Speed = 1.0f;

		SpriteClip(){}
		SpriteClip(std::string name, iVector2 uv = {0, 0}, iVector2 size = { 32,32 }, UINT startFrame = 0, UINT frames = 1, bool hasUpDown = false, bool isLooping = false, float speed = 1.0f, bool isSingle = false)
		{
			Name = name;
			UV = uv;
			Size = size;
			StartFrame = startFrame;
			Frames = frames;
			HasUpDown = hasUpDown;
			IsLooping = isLooping;
			IsSingle = isSingle;
			Speed = speed;
		}
	};

	struct CollisionBox
	{
		int x;
		int y;
		int RadiusX;
		int RadiusY;
	};
	
}
