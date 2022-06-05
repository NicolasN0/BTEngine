#pragma once

#include "Command.h"
#include "SceneChanger.h"
#include "PeterPepperComponent.h"
#include "SelectorComponent.h"
#include "BasicEnemyComponent.h"

namespace dae
{
	

	class Selector final : public  Command
	{
	public:
		Selector(SelectorComponent* const selectorComp,bool goNext,int maxModes) : m_pSelectorComponent(selectorComp), m_GoNext(goNext), m_MaxModes(maxModes) {}
		void Execute(float ) override
		{
		
			if(m_GoNext)
			{
				
				if(m_pSelectorComponent->GetSelected() < m_MaxModes-1)
				{
					m_pSelectorComponent->NextGameMode();
					GameObject* parent = m_pSelectorComponent->GetParent();
					parent->SetPosition(parent->GetPosition().x, parent->GetPosition().y + 40);
				}
			} else
			{
				if (m_pSelectorComponent->GetSelected() > 0)
				{
					m_pSelectorComponent->PreviousGameMode();
					GameObject* parent = m_pSelectorComponent->GetParent();
					parent->SetPosition(parent->GetPosition().x, parent->GetPosition().y - 40);
				}
			
			}
		}
	private:
		SelectorComponent* m_pSelectorComponent;
		int m_MaxModes;
		bool m_GoNext;
	};

	class Continue final: public  Command
	{
	public:
		Continue(SelectorComponent* const selectorComp) : m_pSelectorComponent(selectorComp) {}
		void Execute(float ) override
		{
		
			switch(m_pSelectorComponent->GetSelected())
			{
			case 0:
				SceneChanger::GetInstance().SetCurrentScene("game");
				break;

			case 1:
				SceneChanger::GetInstance().SetCurrentScene("coop");
				break;

			case 2:
				SceneChanger::GetInstance().SetCurrentScene("pvp");
				break;
			}
		}
	private:
		SelectorComponent* m_pSelectorComponent;
		
	};

	class Replay final : public  Command
	{
	public:
		Replay() = default;
		void Execute(float ) override
		{
		
			SceneChanger::GetInstance().SetCurrentScene("start");
		}
	private:
		

	};

	class Throw final : public Command
	{
	public:
		Throw(PeterPepperComponent* const object) : m_pObject(object){}
		void Execute(float ) override
		{
			//Throw salt
			m_pObject->ThrowSalt();

		}
	private:
		PeterPepperComponent* m_pObject;
		
	};

#pragma region movement
	class Move final : public Command
	{
	public:
		Move(PeterPepperComponent* const object, const glm::vec3& moveSpeed) : m_pObject(object), m_MoveSpeed(moveSpeed) {}
		void Execute(float ) override
		{
		
			m_pObject->SetMoveSpeed(m_MoveSpeed);

		}
	private:
		PeterPepperComponent* m_pObject;
		glm::vec3 m_MoveSpeed;
	};

	class StopMove final : public Command
	{
	public:
		StopMove(PeterPepperComponent* const object) : m_pObject(object){};
		void Execute(float ) override
		{
			
			m_pObject->SetMoveSpeed(glm::vec3(0,0,0));

		}
	private:
		PeterPepperComponent* m_pObject;
	};

	class MoveHotdog final : public Command
	{
	public:
		MoveHotdog(BasicEnemyComponent* const object,const glm::vec3& moveSpeed) : m_pObject(object), m_MoveSpeed(moveSpeed) {}
		void Execute(float ) override
		{

			m_pObject->SetDirection(m_MoveSpeed);
			
		}
	private:
		BasicEnemyComponent* m_pObject;
		glm::vec3 m_MoveSpeed;
	};

	class StopMoveHotdog final : public Command
	{
	public:
		StopMoveHotdog(BasicEnemyComponent* const object) : m_pObject(object){}
		void Execute(float ) override
		{

			
			m_pObject->SetDirection(glm::vec3(0,0,0));

		}
	private:
		BasicEnemyComponent* m_pObject;
		
	};

	class NextLevel final : public Command
	{
	public:
		NextLevel(PeterPepperComponent* const object) : m_pObject(object){}
		void Execute(float ) override
		{

			m_pObject->SetNextLevel(true);

		}
	private:
		PeterPepperComponent* m_pObject;
		
	};
	
#pragma endregion movement end
}
