#pragma once
#include "MiniginPCH.h"
#include "Observer.h"


namespace dae
{
	class Subject
	{

	public:
		void addObserver(std::shared_ptr<Observer>pObserver)
		{
			for (auto& observer : m_pObservers)
			{
				if (typeid(*observer) == typeid(*pObserver))
				{
					std::cout << "Subject::AddObserver > Duplicate: " << typeid(*pObserver).name() << " >> Already added!!";
					return;
				}
			}
			m_pObservers.push_back(pObserver);

		}

		void removeObserver(std::shared_ptr<Observer> pObserver)
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
		void notify(GameObject& gameObject, NotifyEvent event)
		{
			for (auto& m_observer : m_pObservers)
			{
				m_observer->onNotify(gameObject, event);
			}
		}
		std::vector<std::shared_ptr<Observer>> m_pObservers;
	};
}
