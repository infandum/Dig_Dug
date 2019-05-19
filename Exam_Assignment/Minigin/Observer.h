#pragma once

namespace dae
{
	class GameObject;
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void onNotify(GameObject& gameObject, NotifyEvent& event) = 0;
	};
}