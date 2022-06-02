#pragma once
#include <iostream>

#include "Command.h"
#include "PeterPepperComponent.h"
#include "SelectorComponent.h"
#include "SceneManager.h"
#include <memory>

#include "SceneChanger.h"
#include "BasicEnemyComponent.h"

namespace dae
{
	

	class Selector : public  Command
	{
	public:
		Selector(SelectorComponent* selectorComp,bool goNext,int maxModes) : m_SelectorComponent(selectorComp), m_GoNext(goNext), m_MaxModes(maxModes) {}
		void Execute(float dt) override
		{
			std::cout << "verander";
			if(m_GoNext)
			{
				
				if(m_SelectorComponent->GetSelected() < m_MaxModes-1)
				{
					m_SelectorComponent->NextGameMode();
					GameObject* parent = m_SelectorComponent->GetParent();
					parent->SetPosition(parent->GetPosition().x, parent->GetPosition().y + 40);
				}
			} else
			{
				if (m_SelectorComponent->GetSelected() > 0)
				{
					m_SelectorComponent->PreviousGameMode();
					GameObject* parent = m_SelectorComponent->GetParent();
					parent->SetPosition(parent->GetPosition().x, parent->GetPosition().y - 40);
				}
			
			}
		}
	private:
		SelectorComponent* m_SelectorComponent;
		int m_MaxModes;
		bool m_GoNext;
	};

	class Continue : public  Command
	{
	public:
		Continue(SelectorComponent* selectorComp) : m_SelectorComponent(selectorComp) {}
		void Execute(float dt) override
		{
			std::cout << "continue?";
			switch(m_SelectorComponent->GetSelected())
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
		SelectorComponent* m_SelectorComponent;
		
	};

	class Replay : public  Command
	{
	public:
		Replay() {}
		void Execute(float dt) override
		{
			std::cout << "Replay?";
			SceneChanger::GetInstance().SetCurrentScene("start");
		}
	private:
		

	};

	class Throw : public Command
	{
	public:
		Throw(PeterPepperComponent* object) : m_pObject(object){};
		void Execute(float dt) override
		{
			//Throw salt
			m_pObject->ThrowSalt();

		};

		PeterPepperComponent* m_pObject;
		
	};

#pragma region movement
	class Move : public Command
	{
	public:
		Move(PeterPepperComponent* object, glm::vec3 moveSpeed) : m_pObject(object), m_MoveSpeed(moveSpeed) {};
		void Execute(float dt) override
		{
			/*if(m_MoveSpeed.y > 0 || m_MoveSpeed.y < 0)
			{
				if(m_pObject->GetIsOnLadder() == true)
				{
					glm::vec3 curPos = m_pObject->GetParent()->GetTransform().GetPosition();
					glm::vec3 furPos = glm::vec3(curPos.x + (m_MoveSpeed.x * dt), curPos.y + (m_MoveSpeed.y * dt),1);


					m_pObject->GetParent()->SetPosition(furPos.x, furPos.y);

					if (m_pObject->GetParent()->IsCenterOverlappingAnyWithTag("Ladder") == false)
					{
						m_pObject->GetParent()->SetPosition(curPos.x, curPos.y);
					}
				}

			}
			
			if(m_MoveSpeed.x > 0 || m_MoveSpeed.x < 0)
			{
				if (m_pObject->GetIsOnPlatform() == true)
				{
					glm::vec3 curPos = m_pObject->GetParent()->GetTransform().GetPosition();
					glm::vec3 furPos = glm::vec3(curPos.x + (m_MoveSpeed.x * dt), curPos.y + (m_MoveSpeed.y * dt), 1);
					m_pObject->GetParent()->SetPosition(furPos.x, furPos.y);

					if (m_pObject->GetParent()->IsCenterOverlappingAnyWithTag("Platform") == false)
					{
						m_pObject->GetParent()->SetPosition(curPos.x, curPos.y);
						
					}

				}
			}*/
			m_pObject->SetMoveSpeed(m_MoveSpeed);

		};

		PeterPepperComponent* m_pObject;
		glm::vec3 m_MoveSpeed;
	};

	class StopMove : public Command
	{
	public:
		StopMove(PeterPepperComponent* object) : m_pObject(object){};
		void Execute(float dt) override
		{
			
			m_pObject->SetMoveSpeed(glm::vec3(0,0,0));

		};

		PeterPepperComponent* m_pObject;
	};

	class MoveHotdog : public Command
	{
	public:
		MoveHotdog(BasicEnemyComponent* object, glm::vec3 moveSpeed) : m_pObject(object), m_MoveSpeed(moveSpeed) {};
		void Execute(float dt) override
		{
			
			/*if (m_MoveSpeed.y > 0 || m_MoveSpeed.y < 0)
			{
				if (m_pObject->GetIsOnLadder() == true)
				{
					glm::vec3 curPos = m_pObject->GetParent()->GetTransform().GetPosition();
					glm::vec3 furPos = glm::vec3(curPos.x + (m_MoveSpeed.x * dt), curPos.y + (m_MoveSpeed.y * dt), 1);


					m_pObject->GetParent()->SetPosition(furPos.x, furPos.y);

					if (m_pObject->GetParent()->IsCenterOverlappingAnyWithTag("Ladder") == false)
					{
						m_pObject->GetParent()->SetPosition(curPos.x, curPos.y);
					}
				}

			}

			if (m_MoveSpeed.x > 0 || m_MoveSpeed.x < 0)
			{
				if (m_pObject->GetIsOnPlatform() == true)
				{
					glm::vec3 curPos = m_pObject->GetParent()->GetTransform().GetPosition();
					glm::vec3 furPos = glm::vec3(curPos.x + (m_MoveSpeed.x * dt), curPos.y + (m_MoveSpeed.y * dt), 1);
					m_pObject->GetParent()->SetPosition(furPos.x, furPos.y);

					if (m_pObject->GetParent()->IsCenterOverlappingAnyWithTag("Platform") == false)
					{
						m_pObject->GetParent()->SetPosition(curPos.x, curPos.y);

					}

				}
			}*/
			m_pObject->SetDirection(m_MoveSpeed);
			
		};

		BasicEnemyComponent* m_pObject;
		glm::vec3 m_MoveSpeed;
	};

	class StopMoveHotdog : public Command
	{
	public:
		StopMoveHotdog(BasicEnemyComponent* object) : m_pObject(object){};
		void Execute(float dt) override
		{

			
			m_pObject->SetDirection(glm::vec3(0,0,0));

		};

		BasicEnemyComponent* m_pObject;
		
	};

	class NextLevel : public Command
	{
	public:
		NextLevel(PeterPepperComponent* object) : m_pObject(object){};
		void Execute(float dt) override
		{

			m_pObject->SetNextLevel(true);

		};

		PeterPepperComponent* m_pObject;
		
	};
	
#pragma endregion movement end
}
