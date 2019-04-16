#pragma once

namespace dae
{
	enum class Event
	{
		EVENT_ENTITY_FELL,
		EVENT_LIFE_CHECK,
		EVENT_GAME_OVER
	};

	class GameObject;
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void onNotify(GameObject& gameObject, Event& event) = 0;
	};
}