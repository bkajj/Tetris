#include "src/States/hpp/GameState.hpp"
#include "src/GameEngine/hpp/Game.hpp"
#include "src/DEFINE.hpp"
#include <iostream>

namespace hgw
{
	GameState::GameState(GameDataRef _data)
	{
		this->_data = _data;
	}

	void GameState::Init()
	{
		for (int i = 0; i < 11; i++)
		{
			verticalLines[i].setSize(sf::Vector2f(1, 600));
			verticalLines[i].setPosition(sf::Vector2f(APP_WIDTH / 2 + i*30 - 150, 100));
		}

		for (int i = 0; i < 21; i++)
		{
			horizontalLines[i].setSize(sf::Vector2f(300, 1));
			horizontalLines[i].setPosition(verticalLines[0].getPosition().x, verticalLines[0].getPosition().y + i * 30);
		}

		sf::RectangleShape temp;
		temp.setFillColor(sf::Color::Red);
		temp.setSize(sf::Vector2f(30, 30));
		temp.setPosition(sf::Vector2f(verticalLines[5].getPosition().x, horizontalLines[0].getPosition().y));
		blocks.push_back(temp);
	}

	void GameState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}

		}
	}

	void GameState::Update(float dt)
	{
		static int clock = 0;

		if (clock < 30)
		{
			clock++;
		}
		else
		{
			blocks[0].move(sf::Vector2f(0, 30));
			clock = 0;
		}
	}

	void GameState::Draw(float dt)
	{
		_data->window.clear();
		
		for (int i = 0; i < 11; i++)
		{
			_data->window.draw(verticalLines[i]);
		}

		for (int i = 0; i < 21; i++)
		{
			_data->window.draw(horizontalLines[i]);
		}

		_data->window.draw(blocks[0]);

		_data->window.display();
	}
}