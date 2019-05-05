#pragma once
#include "SceneManager.h"

namespace dae
{
	class SceneObject;
	class Scene
	{
		friend Scene;
	public:
		void Add(const std::shared_ptr<SceneObject>& object);
		std::string GetName() const { return mName; }

		virtual void Initialize();
		virtual void Update(float deltaTime);
		virtual void Render() const;

		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
		
		explicit Scene(const std::string& name);
	private:
		std::string mName{};
		std::vector <std::shared_ptr<SceneObject>> mObjects{};

		static unsigned int idCounter; 
	};

}
