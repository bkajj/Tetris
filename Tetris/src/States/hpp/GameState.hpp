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
		Figure(FigureType type, sf::Vector2f startPos, bool classicColor, bool isGhostPiece);
		Figure() = default;

<<<<<<< HEAD
		void Init(Figure::FigureType type, sf::Vector2f startCoords, bool classicColor, bool isGhostPiece);
		void Rotate(bool clockwise, bool shouldOffest);
		void moveFigure(sf::Vector2f offset);
		bool testRotationOffset(int oldRotationState, int newRotationState);

		bool willBlockOverlapBlock(float offsetX, float offsetY);
		bool willGridExceed_X(float offestX);
		bool willGridExceed_Y(float offsetY);

		void setColor(sf::Color color);
		void updateGhostCoords();
		bool areCoordsGood();
		static void instaPlace();
=======
		void Rotate(bool clockwise);
		void moveFigure(sf::Vector2f offset, bool isGhostPiece);
		bool testRotationOffset(int oldRotationState, int newRotationState);
		void AddToGrid(short grid_X, short grid_Y, bool isGhostPiece);
		void updateGhostCoords();
>>>>>>> parent of f47acf4... Refactored code a little bit, added ghost piece

		static void setOffsetData();
		
		std::array<sf::RectangleShape, 4> blocks;
		std::array<sf::Vector2f, 4> gridCoords;

		sf::Vector2f leftGridCoord, rightGridCoord, downGridCoord, upGridCoord;

		sf::Color figureColor;
		FigureType _type_;

		static std::map<std::pair<int, int>, sf::Vector2f> JLSTZ_offsetData, I_offsetData;
	private:
		sf::Vector2f* pivot;
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
		static bool willBlockOverlapBlock(std::array<sf::Vector2f, 4> coords);
		static bool willGridExceed_X(int offestX);
		static bool willGridExceed_Y(int offsetY);

		static int random(int min, int max);
		static int negMod(int val);
<<<<<<< HEAD
		static void setNextFigure(bool classicColor);

		static std::vector<int> checkForRow();
		static void destroyFilledRows();
		static Figure::FigureType randFigureType();

=======
		std::vector<int> checkForRow();
		Figure::FigureType randFigureType();
>>>>>>> parent of f47acf4... Refactored code a little bit, added ghost piece
		static std::array<std::array<std::pair<bool, sf::RectangleShape>, 20>, 10> grid;

	private:
		static Figure::FigureType lastType;
		GameDataRef _data;

		sf::Clock gameClock;
<<<<<<< HEAD
		bool isDownKeyPressed = false;
=======
>>>>>>> parent of f47acf4... Refactored code a little bit, added ghost piece

		static Figure currentFigure, ghostFigure;

		std::array<sf::RectangleShape, 11> verticalLines;
		std::array<sf::RectangleShape, 21> horizontalLines;
	};
}