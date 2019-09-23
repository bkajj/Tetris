#include "src/States/hpp/GameState.hpp"
#include "src/GameEngine/hpp/Game.hpp"
#include "src/DEFINE.hpp"
#include <iostream>
#include <chrono>
#include <random>

namespace hgw
{
	Figure::Figure(Figure::FigureType type, sf::Vector2f startPos, sf::Color color) 
	{
		//TODO: maybe delete all Pos vars and do position checking from grid coordinates
		//e.g: if(coord.y > 20) stop moving
		figureColor = color;
		_type_ = type;

		for (int i = 0; i < 4; i++) //set size 30 x 30 and color
		{
			blocks[i].setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
			blocks[i].setFillColor(color);
		}

		switch (type) //create figure shape based on type
		{
		case Figure::I:
			blocks[0].setPosition(startPos.x, startPos.y);
			blocks[1].setPosition(startPos.x, startPos.y + BLOCK_SIZE);
			blocks[2].setPosition(startPos.x, startPos.y + 2 * BLOCK_SIZE);
			blocks[3].setPosition(startPos.x, startPos.y + 3 * BLOCK_SIZE);

			leftPos = blocks[0].getPosition(); //set border position to check overlapping
			rightPos = blocks[0].getPosition();
			downPos = blocks[3].getPosition();
			upPos = blocks[0].getPosition();
			break;
		case Figure::T:
			blocks[0].setPosition(startPos.x, startPos.y);
			blocks[1].setPosition(startPos.x + BLOCK_SIZE, startPos.y);
			blocks[2].setPosition(startPos.x + BLOCK_SIZE, startPos.y + BLOCK_SIZE);
			blocks[3].setPosition(startPos.x + 2 * BLOCK_SIZE, startPos.y);

			leftPos = blocks[0].getPosition();
			rightPos = blocks[3].getPosition();
			downPos = blocks[2].getPosition();
			upPos = blocks[0].getPosition();
			break;
		case Figure::O:
			blocks[0].setPosition(startPos.x, startPos.y);
			blocks[1].setPosition(startPos.x + BLOCK_SIZE, startPos.y);
			blocks[2].setPosition(startPos.x, startPos.y + BLOCK_SIZE);
			blocks[3].setPosition(startPos.x + BLOCK_SIZE, startPos.y + BLOCK_SIZE);

			leftPos = blocks[0].getPosition();
			rightPos = blocks[1].getPosition();
			downPos = blocks[2].getPosition();
			upPos = blocks[0].getPosition();
			break;
		case Figure::L:
			blocks[0].setPosition(startPos.x, startPos.y);
			blocks[1].setPosition(startPos.x, startPos.y + BLOCK_SIZE);
			blocks[2].setPosition(startPos.x, startPos.y + 2 * BLOCK_SIZE);
			blocks[3].setPosition(startPos.x + BLOCK_SIZE, startPos.y + 2 * BLOCK_SIZE);

			leftPos = blocks[0].getPosition();
			rightPos = blocks[3].getPosition();
			downPos = blocks[3].getPosition();
			upPos = blocks[0].getPosition();
			break;
		case Figure::J:
			blocks[0].setPosition(startPos.x + BLOCK_SIZE, startPos.y);
			blocks[1].setPosition(startPos.x + BLOCK_SIZE, startPos.y + BLOCK_SIZE);
			blocks[2].setPosition(startPos.x + BLOCK_SIZE, startPos.y + 2 * BLOCK_SIZE);
			blocks[3].setPosition(startPos.x, startPos.y + 2 * BLOCK_SIZE);

			leftPos = blocks[3].getPosition();
			rightPos = blocks[0].getPosition();
			downPos = blocks[3].getPosition();
			upPos = blocks[0].getPosition();
			break;
		case Figure::S:
			blocks[0].setPosition(startPos.x, startPos.y + BLOCK_SIZE);
			blocks[1].setPosition(startPos.x + BLOCK_SIZE, startPos.y);
			blocks[2].setPosition(startPos.x + BLOCK_SIZE, startPos.y + BLOCK_SIZE);
			blocks[3].setPosition(startPos.x + 2 * BLOCK_SIZE, startPos.y);

			leftPos = blocks[0].getPosition();
			rightPos = blocks[3].getPosition();
			downPos = blocks[0].getPosition();
			upPos = blocks[3].getPosition();
			break;
		case Figure::Z:
			blocks[0].setPosition(startPos.x, startPos.y);
			blocks[1].setPosition(startPos.x + BLOCK_SIZE, startPos.y);
			blocks[2].setPosition(startPos.x + BLOCK_SIZE, startPos.y + BLOCK_SIZE);
			blocks[3].setPosition(startPos.x + 2 * BLOCK_SIZE, startPos.y + BLOCK_SIZE);

			leftPos = blocks[0].getPosition();
			rightPos = blocks[3].getPosition();
			downPos = blocks[3].getPosition();
			upPos = blocks[0].getPosition();
			break;
		}
	}

	void Figure::RotateLeft()
	{
		for (int i = 0; i < 4; i++)
		{
			if (_type_ != FigureType::O)
			{
				sf::Vector2f vec = sf::Vector2f(gridCoords[i].first, gridCoords[i].second);
				sf::Vector2f piv = sf::Vector2f(pivot->first, pivot->second);

				sf::Vector2f absVec = vec - piv;

				sf::Vector2f rotVec = sf::Vector2f(-absVec.y, absVec.x);

				sf::Vector2f vecPrim = rotVec + piv;
				gridCoords[i] = std::make_pair(vecPrim.x, vecPrim.y);
				blocks[i].setPosition(GRID_START_POS_X + gridCoords[i].first * BLOCK_SIZE, GRID_START_POS_Y + gridCoords[i].second * BLOCK_SIZE);
			}	
		}
	}

	void Figure::RotateRight()
	{

	}

	void Figure::AddToGrid(short grid_X, short grid_Y)
	{
		switch (_type_) //set block coordinates on grid
		{
		case Figure::I:
			gridCoords[0] = std::make_pair(grid_X, grid_Y);
			gridCoords[1] = std::make_pair(grid_X, grid_Y + 1);
			gridCoords[2] = std::make_pair(grid_X, grid_Y + 2);
			gridCoords[3] = std::make_pair(grid_X, grid_Y + 3);

			pivot = &gridCoords[2]; //set pivot to rotate
			leftGridCoord = blocks[0].getPosition(); //set border coordinates to check overlapping
			rightGridCoord = blocks[0].getPosition();
			downGridCoord = blocks[3].getPosition();
			upGridCoord = blocks[0].getPosition();
			break;
		case Figure::T:
			gridCoords[0] = std::make_pair(grid_X, grid_Y);
			gridCoords[1] = std::make_pair(grid_X + 1, grid_Y);
			gridCoords[2] = std::make_pair(grid_X + 2, grid_Y);
			gridCoords[3] = std::make_pair(grid_X + 1, grid_Y + 1);

			pivot = &gridCoords[3];
			leftGridCoord = blocks[0].getPosition();
			rightGridCoord = blocks[2].getPosition();
			downGridCoord = blocks[3].getPosition();
			upGridCoord = blocks[0].getPosition();
			break;
		case Figure::O:
			gridCoords[0] = std::make_pair(grid_X, grid_Y);
			gridCoords[1] = std::make_pair(grid_X + 1, grid_Y);
			gridCoords[2] = std::make_pair(grid_X, grid_Y + 1);
			gridCoords[3] = std::make_pair(grid_X + 1, grid_Y + 1);

			pivot = nullptr; //O Figure has no pivot/no rotation
			leftGridCoord = blocks[0].getPosition();
			rightGridCoord = blocks[1].getPosition();
			downGridCoord = blocks[2].getPosition();
			upGridCoord = blocks[0].getPosition();
			break;
		case Figure::L:
			gridCoords[0] = std::make_pair(grid_X, grid_Y);
			gridCoords[1] = std::make_pair(grid_X, grid_Y + 1);
			gridCoords[2] = std::make_pair(grid_X, grid_Y + 2);
			gridCoords[3] = std::make_pair(grid_X + 1, grid_Y + 2);

			pivot = &gridCoords[2];
			leftGridCoord = blocks[0].getPosition();
			rightGridCoord = blocks[3].getPosition();
			downGridCoord = blocks[3].getPosition();
			upGridCoord = blocks[0].getPosition();
			break;
		case Figure::J:
			gridCoords[0] = std::make_pair(grid_X + 1, grid_Y);
			gridCoords[1] = std::make_pair(grid_X + 1, grid_Y + 1);
			gridCoords[2] = std::make_pair(grid_X + 1, grid_Y + 2);
			gridCoords[3] = std::make_pair(grid_X, grid_Y + 2);

			pivot = &gridCoords[2];
			leftGridCoord = blocks[3].getPosition();
			rightGridCoord = blocks[0].getPosition();
			downGridCoord = blocks[3].getPosition();
			upGridCoord = blocks[0].getPosition();
			break;
		case Figure::S:
			gridCoords[0] = std::make_pair(grid_X, grid_Y + 1);
			gridCoords[1] = std::make_pair(grid_X + 1, grid_Y);
			gridCoords[2] = std::make_pair(grid_X + 1, grid_Y + 1);
			gridCoords[3] = std::make_pair(grid_X + 2, grid_Y);

			pivot = &gridCoords[2];
			leftGridCoord = blocks[0].getPosition();
			rightGridCoord = blocks[3].getPosition();
			downGridCoord = blocks[2].getPosition();
			upGridCoord = blocks[1].getPosition();
			break;
		case Figure::Z:
			gridCoords[0] = std::make_pair(grid_X, grid_Y);
			gridCoords[1] = std::make_pair(grid_X + 1, grid_Y);
			gridCoords[2] = std::make_pair(grid_X + 1, grid_Y + 1);
			gridCoords[3] = std::make_pair(grid_X + 2, grid_Y + 1);

			pivot = &gridCoords[2];
			leftGridCoord = blocks[0].getPosition();
			rightGridCoord = blocks[3].getPosition();
			downGridCoord = blocks[3].getPosition();
			upGridCoord = blocks[0].getPosition();
			break;
		}

	}

	GameState::GameState(GameDataRef _data)
	{
		this->_data = _data;
	}

	void GameState::Init()
	{
		for (int i = 0; i < 11; i++) //draw a grid
		{
			verticalLines[i].setSize(sf::Vector2f(1, 600));
			verticalLines[i].setPosition(sf::Vector2f(APP_WIDTH / 2 + i*30 - 150, 100));
		}
		for (int i = 0; i < 21; i++)
		{
			horizontalLines[i].setSize(sf::Vector2f(300, 1));
			horizontalLines[i].setPosition(verticalLines[0].getPosition().x, verticalLines[0].getPosition().y + i * 30);
		}

		gameClock.restart(); //start clock that moves blocks
		
		int figure = random(0, 6); //create new Figure with random color and random shape
		sf::Color color = sf::Color(random(0, 255), random(0, 255), random(0, 255), 255);
		currentFigure = Figure(static_cast<Figure::FigureType>(figure), sf::Vector2f(GRID_START_POS_X, GRID_START_POS_Y), color);
		currentFigure.AddToGrid(0, 0);
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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && currentFigure.rightPos.x <= GRID_END_POS_X - 2 * BLOCK_SIZE) //move right
			{
				for (int i = 0; i < 4; i++)
				{
					currentFigure.blocks[i].move(BLOCK_SIZE, 0); //move blocks to right by 30 
					currentFigure.gridCoords[i].first++; //set proper grid coords
				}
				currentFigure.rightPos.x += BLOCK_SIZE; //update border positons
				currentFigure.leftPos.x += BLOCK_SIZE;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && currentFigure.leftPos.x >= GRID_START_POS_X + BLOCK_SIZE) //move left
			{
				for (int i = 0; i < 4; i++)
				{
					currentFigure.blocks[i].move(-BLOCK_SIZE, 0); //move blocks to left by 30 
					currentFigure.gridCoords[i].first--; //set proper grid coords
				}
				currentFigure.leftPos.x -= BLOCK_SIZE; //update border positons
				currentFigure.rightPos.x -= BLOCK_SIZE;
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) //rotate left
			{
				currentFigure.RotateLeft();
			}
		}
	}

	void GameState::Update(float dt)
	{
		if (gameClock.getElapsedTime() >= sf::seconds(0.5) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) //Figure falling + fast fall
		{
			for (int i = 0; i < 4; i++)
			{
				currentFigure.blocks[i].move(0, BLOCK_SIZE); //move blocks down by 30
				currentFigure.gridCoords[i].second++; //set proper grid coords
			}
			currentFigure.downPos.y += BLOCK_SIZE; //update border positons
			currentFigure.upPos.y += BLOCK_SIZE;

			gameClock.restart();
		}

		if (currentFigure.downPos.y >= GRID_END_POS_Y - BLOCK_SIZE || willBlockOverlap()) //stop figure
		{
			for (int i = 0; i < 4; i++) //add to grid
			{
				grid[currentFigure.gridCoords[i].first][currentFigure.gridCoords[i].second] = std::make_pair(true, currentFigure.blocks[i]);
			}

			int nextFigure = random(0, 6); //create next figure
			sf::Color nextColor = sf::Color(random(0, 255), random(0, 255), random(0, 255), 255);
			currentFigure = Figure(static_cast<Figure::FigureType>(nextFigure), sf::Vector2f(GRID_START_POS_X, GRID_START_POS_Y), nextColor);
			currentFigure.AddToGrid(0, 0);
		}

	}

	void GameState::Draw(float dt)
	{
		_data->window.clear();
		
		for (auto &block : currentFigure.blocks) //draw current figure
		{
			_data->window.draw(block);
		}

		for (int i = 0; i < 10; i++) //draw solid blocks
		{
			for (int j = 0; j < 20; j++)
			{
				if (grid[i][j].first == true) //if block is on grid
				{
					_data->window.draw(grid[i][j].second);
				}
			}
		}

		for (int i = 0; i < 11; i++) //draw grid
		{
			_data->window.draw(verticalLines[i]);
		}
		for (int i = 0; i < 21; i++)
		{
			_data->window.draw(horizontalLines[i]);
		}

		_data->window.display();
	}

	bool GameState::willBlockOverlap()
	{
		for (int i = 0; i < 4; i++)
		{
			if (grid[currentFigure.gridCoords[i].first][currentFigure.gridCoords[i].second + 1].first == true)
			{
				return true;
			}
		}
		return false;
	}

	int GameState::random(int min, int max)
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 gen(seed);
		std::uniform_int<int> distrib(min, max);
		return distrib(gen);
	}
}