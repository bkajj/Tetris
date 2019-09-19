#pragma once
#include "src/GameEngine/hpp/State.hpp"
#include "src/GameEngine/hpp/Game.hpp"
#include <array>

namespace hgw
{
	class Figure
	{
	public:
		enum FigureType { I, T, O, L, J, S, Z};
		Figure(FigureType type, sf::Vector2f startPos, sf::Color color);

		std::array<sf::RectangleShape, 4> blocks;
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

	private:
		GameDataRef _data;

		std::array<sf::RectangleShape, 11> verticalLines;
		std::array<sf::RectangleShape, 21> horizontalLines;

		std::vector<sf::RectangleShape> blocks;

		Figure I = Figure(Figure::I, sf::Vector2f(400, 100), sf::Color::Red);
		Figure T = Figure(Figure::T, sf::Vector2f(250, 100), sf::Color::White);
		Figure O = Figure(Figure::O, sf::Vector2f(400, 190), sf::Color::Blue);
		Figure L = Figure(Figure::L, sf::Vector2f(250, 130), sf::Color::Yellow);
		Figure J = Figure(Figure::J, sf::Vector2f(400, 220), sf::Color::Magenta);
		Figure S = Figure(Figure::S, sf::Vector2f(250, 310), sf::Color::Cyan);
		Figure Z = Figure(Figure::Z, sf::Vector2f(400, 310), sf::Color::Green);
	};
}