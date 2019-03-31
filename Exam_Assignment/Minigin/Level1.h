#pragma once
#include "Scene.h"

namespace dae{
class Level1 final : public Scene
{
public:
	Level1();
	~Level1() = default;

	void Initialize() override;

	Level1(const Level1& other) = delete;
	Level1(Level1&& other) = delete;
	Level1& operator=(const Level1& other) = delete;
	Level1& operator=(Level1&& other) = delete;

};
}