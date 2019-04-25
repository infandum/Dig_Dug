#pragma once
#include "MiniginPCH.h"
#include <windows.h>
namespace dae
{
	enum class StatusCode
	{
		STATUS_SUCCES,
		STATUS_ERROR
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
		int Magnitude() const;
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
		x /= magnitude;
		y /= magnitude;
		return StatusCode::STATUS_SUCCES;
	}

	inline int iVector2::Magnitude() const
	{
		return static_cast<int>(std::sqrt(x * x + y * y));
	}
	

	enum class NotifyEvent
	{
		EVENT_SPAWN,
		EVENT_IDLE,
		EVENT_MOVE,
		EVENT_DIG,
		EVENT_ATTACK,
		EVENT_HIT,
		EVENT_DEAD,
		EVENT_CRUSHED,
	};

	enum class Direction
	{
		RIGHT = 0,
		UP = 1,
		LEFT = 2,
		DOWN = 3,
		NONE = 4
		/*UP = 0,
		DOWN = 1,
		LEFT = 2,
		RIGHT = 3,
		NONE = 4*/
	};

	enum InputTriggerState
	{
		Pressed,
		Released,
		Down
	};

	enum class TileState
	{
		DIRT,
		DUG,
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
		ButtonRightTrigger = 0x0200
	};

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
		iVector2 UV = { 0 , 0 };
		UINT StartFrame = 0;
		UINT frames = 1;
		bool hasUpDown = false;
		bool isLooping = false;
	};


	
}
