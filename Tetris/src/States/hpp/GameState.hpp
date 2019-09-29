#pragma once
#include "src/GameEngine/hpp/State.hpp"
#include "src/GameEngine/hpp/Game.hpp"
#include <array>
#include <vector>
#include <unordered_map>

namespace hgw
{
	class Figure
	{
	public:
		enum FigureType { I, T, O, L, J, S, Z};
		Figure(FigureType type, sf::Vector2f startPos, bool classicColor);
		Figure() = default;

		void Rotate(bool clockwise);
		void moveFigure(sf::Vector2f offset);
		bool testRotationOffset(int oldRotationState, int newRotationState);
		void AddToGrid(short grid_X, short grid_Y);
		static void setOffsetData();
		
		std::array<sf::RectangleShape, 4> blocks;
		std::array<sf::Vector2f, 4> gridCoords;

		sf::Vector2f leftGridCoord, rightGridCoord, downGridCoord, upGridCoord;

		sf::Color figureColor;
		FigureType _type_;

		static std::map<std::pair<int, int>, sf::Vector2f> JLSTZ_offsetData, I_offsetData, O_offsetData;
	private:
		sf::Vector2f* pivot;
		sf::Vector2f I_case_pivot;
		int rotationState = 0;
	};

	class GameState : public State
	{
	public:
		GameState(GameDataRef _data);
		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

		static bool willBlockOverlapBlock(int offsetX, int offsetY);
		static bool willGridExceed_X(int offestX);
		static bool willGridExceed_Y(int offsetY);

		static int random(int min, int max);
		static int negMod(int val);
		std::vector<int> checkForRow();
		Figure::FigureType randFigureType();
		static std::array<std::array<std::pair<bool, sf::RectangleShape>, 20>, 10> grid;

	private:
		Figure::FigureType lastType;
		GameDataRef _data;

		sf::Clock gameClock;

		static Figure currentFigure;

		std::array<sf::RectangleShape, 11> verticalLines;
		std::array<sf::RectangleShape, 21> horizontalLines;
	};
}