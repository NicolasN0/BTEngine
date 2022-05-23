#pragma once
#include <iostream>

#include "Command.h"
#include "PeterPepperComponent.h"
#include "SceneManager.h"
#include <memory>
namespace dae
{
	


	class DamagePlayer : public Command
	{
	public:
		DamagePlayer(PeterPepperComponent* valuesComp) : m_pComp(valuesComp)
		{
			
		};
		void Execute(float dt) override
		{
			m_pComp->Damage();
		};
	private:
		PeterPepperComponent* m_pComp;
	};

	class Fire : public Command
	{
	public:
		void Execute(float dt) override
		{
			std::cout << "Fire";
		};
	};

	class Duck : public Command
	{
	public:
		void Execute(float dt) override
		{
			std::cout << "Duck";
		};
	};

	class Crouch : public Command
	{
	public:
		void Execute(float dt) override
		{
			std::cout << "Crouch";
		};
	};

	class Fart : public Command
	{
	public:
		void Execute(float dt) override
		{
			std::cout << "Fart";
		};
	};


#pragma region movement
	class Move : public Command
	{
	public:
		//Move(std::shared_ptr<GameObject> object, glm::vec3 moveSpeed) : m_pObject(object), m_MoveSpeed(moveSpeed) {};
		Move(PeterPepperComponent* object, glm::vec3 moveSpeed) : m_pObject(object), m_MoveSpeed(moveSpeed) {};
		void Execute(float dt) override
		{
			if(m_MoveSpeed.y > 0 || m_MoveSpeed.y < 0)
			{
				if(m_pObject->GetIsOnLadder() == true)
				{
					glm::vec3 curPos = m_pObject->GetParent()->GetTransform().GetPosition();
					glm::vec3 furPos = glm::vec3(curPos.x + (m_MoveSpeed.x * dt), curPos.y + (m_MoveSpeed.y * dt),1);
					//m_pObject->GetParent()->SetPosition(curPos.x + (m_MoveSpeed.x * dt), curPos.y + (m_MoveSpeed.y * dt));

					m_pObject->GetParent()->SetPosition(furPos.x, furPos.y);

					if(m_pObject->GetParent()->IsOverlappingAnyWithTag("Ladder") == false)
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
					if (m_pObject->GetParent()->IsOverlappingAnyWithTag("Platform") == false)
					{
						m_pObject->GetParent()->SetPosition(curPos.x, curPos.y);
					}

				}
			}


		};
		//std::shared_ptr<GameObject> m_pObject;
		PeterPepperComponent* m_pObject;
		glm::vec3 m_MoveSpeed;
	};

	
#pragma endregion movement end
}