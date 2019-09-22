#pragma once
#include "src/GameEngine/hpp/State.hpp"
#include "src/GameEngine/hpp/Game.hpp"
#include <array>
#include <vector>

namespace hgw
{
	class Figure
	{
	public:
		enum FigureType { I, T, O, L, J, S, Z};
		Figure(FigureType type, sf::Vector2f startPos, sf::Color color);
		Figure() = default;

		void RotateLeft();
		void RotateRight();

		void AddToGrid(short grid_X, short grid_Y);
		
		std::array<sf::RectangleShape, 4> blocks;
		std::array<std::pair<short, short>, 4> gridCoords;

		sf::Vector2f leftPos, rightPos, downPos, upPos;
		sf::Vector2f leftGridCoord, rightGridCoord, downGridCoord, upGridCoord;

		sf::Color figureColor;
	private:

		short rotation = 0;
		std::pair<short, short>* pivot;

		
		FigureType _type_;
	};

	class GameState : public State
	{
	public:
		GameState(GameDataRef _data);
		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

		bool willBlockOverlap();
		int random(int min, int max);

	private:
		GameDataRef _data;

		sf::Clock gameClock;

		Figure currentFigure;

		std::array<std::array<std::pair<bool, sf::RectangleShape>, 20>, 10> grid;
		std::array<sf::RectangleShape, 11> verticalLines;
		std::array<sf::RectangleShape, 21> horizontalLines;
	};
}