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

	void Figure::RotateLeft()
	{

	}

	void Figure::RotateRight()
	{

	}

	void Figure::AddToGrid(short grid_X, short grid_Y)
	{
		switch (_type_)
		{
		case hgw::Figure::I:
			gridCoords[0] = std::make_pair(grid_X, grid_Y);
			gridCoords[1] = std::make_pair(grid_X, grid_Y + BLOCK_SIZE);
			gridCoords[2] = std::make_pair(grid_X, grid_Y + 2 * BLOCK_SIZE);
			gridCoords[3] = std::make_pair(grid_X, grid_Y + 3 * BLOCK_SIZE);
			break;
		case hgw::Figure::T:
			break;
		case hgw::Figure::O:
			break;
		case hgw::Figure::L:
			break;
		case hgw::Figure::J:
			break;
		case hgw::Figure::S:
			break;
		case hgw::Figure::Z:
			break;
		default:
			break;
		}

		gridCoords[0] = std::make_pair(grid_X, grid_Y);
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
	}

	void GameState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			std::cout << "X: " << _data->input.GetMousePosition(_data->window).x << "  Y: " << _data->input.GetMousePosition(_data->window).x << std::endl;
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}

		}
	}

	void GameState::Update(float dt)
	{

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

		_data->window.display();
	}
}