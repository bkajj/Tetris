#pragma once
#include "src/GameEngine/hpp/State.hpp"
#include "src/GameEngine/hpp/Game.hpp"
#include <array>

namespace hgw
{
	class Figure
	{

	};

	class GameState : public State
	{
	public:
		GameState(GameDataRef _data);
		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		std::array<sf::RectangleShape, 11> verticalLines;
		std::array<sf::RectangleShape, 21> horizontalLines;

		std::vector<sf::RectangleShape> blocks;
	};
}