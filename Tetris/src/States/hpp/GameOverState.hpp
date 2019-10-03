#include "src/GameEngine/hpp/State.hpp"
#include "src/GameEngine/hpp/Game.hpp"
#pragma once

namespace hgw
{
	class GameOverState : public State
	{
	public:
		GameOverState(GameDataRef _data);
		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Text gameOverText, restartText, settingsText, exitText;
	};
}