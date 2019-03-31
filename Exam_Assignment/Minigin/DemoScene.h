#pragma once
#include "Scene.h"

namespace dae
{
	class DemoScene final : public Scene
	{
	public:
		DemoScene();
		~DemoScene() = default;

		void Initialize() override;
		
		DemoScene(const DemoScene& other) = delete;
		DemoScene(DemoScene&& other) = delete;
		DemoScene& operator=(const DemoScene& other) = delete;
		DemoScene& operator=(DemoScene&& other) = delete;
	};
}