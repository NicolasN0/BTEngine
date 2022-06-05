#pragma once
#include <MonoBehaviour.h>
namespace dae
{
	
	class ValuesComponent :
	    public MonoBehaviour
	{

	public:
		//Rule of 5
		ValuesComponent();
		~ValuesComponent();

		ValuesComponent(const ValuesComponent&) = delete;
		ValuesComponent(ValuesComponent&&) noexcept = delete;

		ValuesComponent& operator=(const ValuesComponent&) = delete;
		ValuesComponent& operator=(ValuesComponent&&) noexcept = delete;
		//Core
		virtual void Update(float dt);
		virtual void FixedUpdate(float timestep);

		//Getter
		int GetLives() const;
		int GetScores() const;
		int GetPeppers() const;

		//Setter
		void SetSubject(Subject* subject);
		void SetLives(int lives);

		//Public functions
		void Damage();
		void IncreaseScore(int score);
		void DecreasePeppers();
		void ResetObserver();

		//Static function
		static void Reset();
	private:
		static int m_Lives;
		static int m_Score;
		static int m_Peppers;

		Subject* m_Subject;
	};
}

