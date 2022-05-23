#pragma once
namespace dae
{
	class Minigin;

	class Command
	{
	public:

		virtual ~Command() = default;
		virtual void Execute(float dt) = 0;

	};

	class QuitGame final : public Command
	{
	public:
		QuitGame(dae::Minigin* pEngine);
		void Execute(float dt) override;
	private:
		dae::Minigin* m_pEngine;
	};
}