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
		Figure();

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

		static void setOffsetData();
		
		std::array<sf::RectangleShape, 4> blocks;
		std::array<sf::Vector2f, 4> gridCoords;

		sf::Color figureColor;
		FigureType _type_;
		
		static std::map<std::pair<int, int>, sf::Vector2f> JLSTZ_offsetData, I_offsetData;
		int rotationState = 0;
	private:
		sf::Vector2f* pivot;

		bool isGhost;
		
	};

	class GameState : public State
	{
	public:
		GameState(GameDataRef _data);
		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

		static int random(int min, int max);
		static int negMod(int val);
		static void setNextFigure(bool classicColor);

		static std::vector<int> checkForRow();
		static void destroyFilledRows();
		static Figure::FigureType randFigureType();

		static std::array<std::array<std::pair<bool, sf::RectangleShape>, 20>, 10> grid;
		static Figure currentFigure, ghostFigure;

	private:
		static Figure::FigureType lastType;
		GameDataRef _data;

		sf::Clock gameClock;
		bool isDownKeyPressed = false;


		std::array<sf::RectangleShape, 11> verticalLines;
		std::array<sf::RectangleShape, 21> horizontalLines;
	};
}