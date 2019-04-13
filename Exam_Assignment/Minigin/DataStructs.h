#pragma once
namespace dae
{
	enum class CompType
	{
		BASECOMPONENT,
		TRANSFROMCOMPONENT,
		FPSCOMPONENT,
		TEXTCOMPONENT,
		RENDERCOMPONENT,
		TEXTURECOMPONENT
	};

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
		fVector2(float x, float y) :x(x), y(y){}
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
}
