#pragma once


namespace dae
{
	class Observer;
	class GameObject;
	enum class Event;

	class Subject final
	{
	public:
		Subject() = default;
		~Subject();

		Subject(const Subject&) = delete;
		Subject(Subject&&) noexcept = delete;
		Subject& operator= (const Subject&) = delete;
		Subject& operator= (const Subject&&) noexcept = delete;

		void AddObserver(Observer* const observer);
		void RemoveObserver(Observer* const observer);

		void Notify(const GameObject& go, Event event);

	private:
		std::vector<Observer*> m_pObservers;

	};
}

