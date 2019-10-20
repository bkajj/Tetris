#pragma once
#include "src/GameEngine/hpp/State.hpp"
#include "src/GameEngine/hpp/Game.hpp"
#include <fstream>

namespace hgw
{
	class MenuState : public State
	{
	public:
		MenuState(GameDataRef _data);
		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	
	private:
		void loadAllVariablesFromFile();

		GameDataRef _data;

		sf::Text tetrisText;
		sf::Text startText;
		sf::Text settingsText;
		sf::Text exitText;

		std::fstream dataFile;
	};
}