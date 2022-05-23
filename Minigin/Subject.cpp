#include "MiniginPCH.h"
#include "Subject.h"
#include "Observer.h"

dae::Subject::~Subject()
{
	for(auto observer : m_Observers)
	{
		delete observer;
		observer = nullptr;
	}
}

void dae::Subject::AddObserver(Observer* observer)
{
	m_Observers.push_back(observer);
	
}

void dae::Subject::RemoveObserver(Observer* observer)
{
	m_Observers.erase(std::remove(m_Observers.begin(),m_Observers.end(),observer),m_Observers.end());
}

void dae::Subject::Notify(const GameObject& go, Event event)
{
	for(int i{}; i < m_Observers.size();i++)
	{
		m_Observers.at(i)->Notify(go, event);
	}
}
