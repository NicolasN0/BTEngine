#pragma once


namespace dae
{
	class Observer;
	class GameObject;
	enum class Event;

	class Subject
	{
	public:
		~Subject();
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);

		void Notify(const GameObject& go, Event event);
	//protected:

	private:
		std::vector<Observer*> m_Observers;

	};
}

