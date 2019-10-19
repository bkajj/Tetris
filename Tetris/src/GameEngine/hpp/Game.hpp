#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "GraphicsManager.hpp"
#include "InputManager.hpp"

namespace hgw
{
	struct saveVariables
	{
		int highScore;

		bool fullGrid;
		bool originalColors;
	};

	struct GameData
	{
		StateMachine machine;
		sf::RenderWindow window;
		GraphicsManager graphics;
		InputManager input;

		saveVariables saveVariables;
		enum variableNames { highScore, fullGrid, originalColors };
	};

	typedef std::shared_ptr<GameData> GameDataRef;

	class Game
	{
	public:
		Game(int width, int height, std::string title);

	private:
		const float dt = 1.0f / 60.0f;
		sf::Clock _clock;

		GameDataRef _data = std::make_shared<GameData>();

		void Run();
	};





}