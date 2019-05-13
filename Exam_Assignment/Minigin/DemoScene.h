#pragma once
#include "Scene.h"

namespace dae
{
	class DemoScene final : public Scene
	{
	public:
		
		DemoScene();
		virtual ~DemoScene() = default;

		DemoScene(const DemoScene& other) = delete;
		DemoScene(DemoScene&& other) = delete;
		DemoScene& operator=(const DemoScene& other) = delete;
		DemoScene& operator=(DemoScene&& other) = delete;

		void Initialize() override;

	};
}