#include "src/States/hpp/GameState.hpp"
#include "src/GameEngine/hpp/Game.hpp"
#include "src/DEFINE.hpp"
#include <iostream>

namespace hgw
{
	Figure::Figure(Figure::FigureType type, sf::Vector2f startPos, sf::Color color)
	{
		for (int i = 0; i < 4; i++)
		{
			blocks[i].setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
			blocks[i].setFillColor(color);
		}
		switch (type)
		{
		case Figure::I:
			for (int i = 0; i < 4; i++)
			{		
				blocks[i].setPosition(startPos.x, startPos.y + i * BLOCK_SIZE);
			}
			break;
		case Figure::T:
			for (int i = 0; i < 3; i++)
			{
				blocks[i].setPosition(startPos.x + i * BLOCK_SIZE, startPos.y);
			}
			blocks[3].setPosition(startPos.x + BLOCK_SIZE, startPos.y + BLOCK_SIZE);
			break;
		case Figure::O:
			for (int i = 0; i < 2; i++)
			{
				blocks[i].setPosition(startPos.x + i * BLOCK_SIZE, startPos.y);
			}
			for (int i = 2; i < 4; i++)
			{
				blocks[i].setPosition(startPos.x + (i-2) * BLOCK_SIZE, startPos.y + BLOCK_SIZE);
			}
			break;
		case Figure::L:
			for (int i = 0; i < 3; i++)
			{
				blocks[i].setPosition(startPos.x, startPos.y + i * BLOCK_SIZE);
			}
			blocks[3].setPosition(startPos.x + BLOCK_SIZE, startPos.y + 2 * BLOCK_SIZE);
			break;
		case Figure::J:
			blocks[0].setPosition(startPos.x, startPos.y + 2 * BLOCK_SIZE);
			for (int i = 1; i < 4; i++)
			{
				blocks[i].setPosition(startPos.x + BLOCK_SIZE, startPos.y + (i-1) * BLOCK_SIZE);
			}
			break;
		case Figure::S:
			blocks[0].setPosition(startPos.x, startPos.y + BLOCK_SIZE);
			blocks[1].setPosition(startPos.x + BLOCK_SIZE, startPos.y);
			blocks[2].setPosition(startPos.x + BLOCK_SIZE, startPos.y + BLOCK_SIZE);
			blocks[3].setPosition(startPos.x + 2 * BLOCK_SIZE, startPos.y);
			break;
		case Figure::Z:
			blocks[0].setPosition(startPos.x, startPos.y);
			blocks[1].setPosition(startPos.x + BLOCK_SIZE, startPos.y);
			blocks[2].setPosition(startPos.x + BLOCK_SIZE, startPos.y + BLOCK_SIZE);
			blocks[3].setPosition(startPos.x + 2 * BLOCK_SIZE, startPos.y + BLOCK_SIZE);
			break;
		}
	}

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

		for (int i = 0; i < 4; i++)
		{
			_data->window.draw(I.blocks[i]);
			_data->window.draw(T.blocks[i]);
			_data->window.draw(O.blocks[i]);
			_data->window.draw(L.blocks[i]);
			_data->window.draw(J.blocks[i]);
			_data->window.draw(S.blocks[i]);
			_data->window.draw(Z.blocks[i]);
		}

		_data->window.draw(blocks[0]);

		_data->window.display();
	}
}