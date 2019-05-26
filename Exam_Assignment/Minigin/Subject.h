#pragma once
#include "MiniginPCH.h"
#include "Observer.h"


namespace dae
{
	class Subject
	{

	public:
		void AddObserver(std::shared_ptr<Observer>pObserver)
		{
			for (auto& observer : m_pObservers)
			{
				if (observer == pObserver)
				{
					std::cout << "Subject::AddObserver > Duplicate: " << typeid(*pObserver).name() << " >> Already added!!";
					return;
				}
			}
			m_pObservers.push_back(pObserver);

		}

		void RemoveObserver(std::shared_ptr<Observer> pObserver)
		{
			const auto observer = std::find(m_pObservers.begin(), m_pObservers.end(), pObserver);
			if (observer == m_pObservers.end())
			{
				std::cout << "Subject::RemoveObserver > Observer NOT FOUND!" << std::endl;
				return;
			}
			m_pObservers.erase(observer);
		}

	protected:
		void Notify(GameObject& gameObject, NotifyEvent event)
		{
			for (auto& m_observer : m_pObservers)
			{
				m_observer->onNotify(gameObject, event);
			}
		}
		std::vector<std::shared_ptr<Observer>> m_pObservers;
	};
}
