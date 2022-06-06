#include "MiniginPCH.h"
#include "Subject.h"
#include "Observer.h"

dae::Subject::~Subject()
{

	for(auto observer : m_pObservers)
	{
		delete observer;
		observer = nullptr;
	}
}

void dae::Subject::AddObserver(Observer* const observer)
{
	m_pObservers.push_back(observer);
	
}

void dae::Subject::RemoveObserver(Observer* const observer)
{
	m_pObservers.erase(std::remove(m_pObservers.begin(),m_pObservers.end(),observer),m_pObservers.end());
}

void dae::Subject::Notify(const GameObject& go, Event event)
{
	for(unsigned int i{}; i < m_pObservers.size();i++)
	{
		m_pObservers.at(i)->Notify(go, event);
	}
}
