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
			for (auto& observ : m_pObservers)
			{
				if (typeid(*observ) == typeid(*pObserver))
				{
					std::cout << "Observer::AddObserver > Duplicate: " << typeid(*pObserver).name() << " >> Already added!!";
					return;
				}
			}
			m_pObservers.push_back(pObserver);

		}

		void removeObserver(std::shared_ptr<Observer> pObserver)
		{
			const auto comp = std::find(m_pObservers.begin(), m_pObservers.end(), pObserver);
			if (comp == m_pObservers.end())
			{
				std::wcout << L"Observer::RemoveObserver > Observer is not attached to this GameObject!" << std::endl;
				return;
			}
			m_pObservers.erase(comp);
		}

	protected:
		void notify(GameObject& gameObject, Event event)
		{
			for (auto& m_observer : m_pObservers)
			{
				m_observer->onNotify(gameObject, event);
			}
		}
		std::vector<std::shared_ptr<Observer>> m_pObservers;
	};
}
