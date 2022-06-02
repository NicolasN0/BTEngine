#pragma once
#include <MonoBehaviour.h>
namespace dae
{
	
	class ValuesComponent :
	    public MonoBehaviour
	{

	public:
		~ValuesComponent();
		virtual void Update(float dt);
		virtual void FixedUpdate(float timestep);
		void Damage();
		void IncreaseScore(int score);
		void SetSubject(Subject* subject);

		int GetLives() const;
		void SetLives(int lives);
		int GetScores() const;

		static void Reset();
	private:
		static int m_Lives;
		static int m_Score;
		//int m_Lives{3};
		//int m_Score{};
		Subject* m_Subject{};
	};
}

