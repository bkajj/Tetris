#pragma once
#include "src/GameEngine/hpp/State.hpp"
#include "src/GameEngine/hpp/Game.hpp"
#include <array>
#include <fstream>
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
		bool areCoordsGood();
		void updateGhostCoords();

		bool willBlockOverlapBlock(float offsetX, float offsetY);
		bool willGridExceed_X(float offestX);
		bool willGridExceed_Y(float offsetY);
			
		void instaPlace();
		void setColor(sf::Color color);
		void setOffsetData();

		FigureType randFigureType(FigureType notToRepeatType);
		FigureType randFigureType();
			
		static std::map<std::pair<int, int>, sf::Vector2f> JLSTZ_offsetData, I_offsetData;

		std::array<sf::RectangleShape, 4> blocks;
		std::array<sf::Vector2f, 4> gridCoords;

		sf::Color figureColor;
		FigureType _type_;
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

		void setNextFigures(bool classicColor);
		std::vector<int> checkForRow();
		void destroyFilledRows();

		std::string insertZeros(int value, int digits);

		static void updateGameData(GameData::variableNames variableName, int variableValue, GameDataRef _data);
		static int getGameDataFromFile(GameData::variableNames variableName);
		
		static std::array<std::array<std::pair<bool, sf::RectangleShape>, 20>, 10> grid;
		static Figure currentFigure, ghostFigure, nextFigure;
		static std::string varNameAsStr(GameData::variableNames varName);
		static GameData::variableNames asVarName(std::string varNameAsStr);

		int totalRowsCleaned;
		int score;
		static std::fstream dataFile;
	
	private:
		GameDataRef _data;
		sf::Sound clear1, clear2, clear3, clear4;
		sf::Music gameMusic;

		std::array<int, 30> level = { 48, 43, 38, 33, 28, 23, 18, 13, 8, 6, 5, 5, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 };
		unsigned int currLvl = 0;
		sf::Text scoreText, highScoreText, nextFigureText, linesText, statsText;
		std::unordered_map<Figure::FigureType, std::pair<Figure, int>> stats;
		std::unordered_map<Figure::FigureType, sf::Text> eachStatText;

		sf::Clock dropClock, moveClock;
		bool isDownKeyPressed = false;

		std::array<sf::RectangleShape, 11> verticalLines;
		std::array<sf::RectangleShape, 21> horizontalLines;
	};

	int random(int min, int max);
	int negMod(int val);

	
}