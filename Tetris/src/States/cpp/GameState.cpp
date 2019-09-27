#include "src/States/hpp/GameState.hpp"
#include "src/GameEngine/hpp/Game.hpp"
#include "src/DEFINE.hpp"
#include <iostream>
#include <chrono>
#include <math.h>
#include <random>

namespace hgw
{
	Figure::Figure(Figure::FigureType type, sf::Vector2f startPos, bool classicColor) 
	{
		_type_ = type;

		for (int i = 0; i < 4; i++) //set size 30 x 30 and color
		{
			blocks[i].setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
			if (!classicColor)
			{
				blocks[i].setFillColor(sf::Color(GameState::random(0, 255), GameState::random(0, 255), GameState::random(0, 255), 255));
			}
		}

		switch (type) //create figure shape based on type
		{
		case Figure::I:
			blocks[0].setPosition(startPos.x, startPos.y);
			blocks[1].setPosition(startPos.x + BLOCK_SIZE, startPos.y);
			blocks[2].setPosition(startPos.x + 2 * BLOCK_SIZE, startPos.y);
			blocks[3].setPosition(startPos.x + 3 * BLOCK_SIZE, startPos.y);
			if (classicColor)
			{
				for (int i = 0; i < 4; i++) //set size 30 x 30 and color
				{
					blocks[i].setFillColor(sf::Color::Cyan); 
				}
			}
			break;
		case Figure::T:
			blocks[0].setPosition(startPos.x, startPos.y + BLOCK_SIZE);
			blocks[1].setPosition(startPos.x + BLOCK_SIZE, startPos.y + BLOCK_SIZE);
			blocks[2].setPosition(startPos.x + 2 * BLOCK_SIZE, startPos.y + BLOCK_SIZE);
			blocks[3].setPosition(startPos.x + BLOCK_SIZE, startPos.y);
			if (classicColor)
			{
				for (int i = 0; i < 4; i++) //set size 30 x 30 and color
				{
					blocks[i].setFillColor(sf::Color(128, 0, 128, 255)); //purple
				}
			}
			break;
		case Figure::O:
			blocks[0].setPosition(startPos.x, startPos.y);
			blocks[1].setPosition(startPos.x + BLOCK_SIZE, startPos.y);
			blocks[2].setPosition(startPos.x, startPos.y + BLOCK_SIZE);
			blocks[3].setPosition(startPos.x + BLOCK_SIZE, startPos.y + BLOCK_SIZE);
			if (classicColor)
			{
				for (int i = 0; i < 4; i++) //set size 30 x 30 and color
				{
					blocks[i].setFillColor(sf::Color::Yellow);
				}
			}
			break;
		case Figure::L:
			blocks[0].setPosition(startPos.x, startPos.y + BLOCK_SIZE);
			blocks[1].setPosition(startPos.x + BLOCK_SIZE, startPos.y + BLOCK_SIZE);
			blocks[2].setPosition(startPos.x + 2 * BLOCK_SIZE, startPos.y + BLOCK_SIZE);
			blocks[3].setPosition(startPos.x + 2 * BLOCK_SIZE, startPos.y);
			if (classicColor)
			{
				for (int i = 0; i < 4; i++) //set size 30 x 30 and color
				{
					blocks[i].setFillColor(sf::Color(255, 165, 0, 255)); //orange
				}
			}
			break;
		case Figure::J:
			blocks[0].setPosition(startPos.x, startPos.y);
			blocks[1].setPosition(startPos.x, startPos.y + BLOCK_SIZE);
			blocks[2].setPosition(startPos.x + BLOCK_SIZE, startPos.y + BLOCK_SIZE);
			blocks[3].setPosition(startPos.x + 2 * BLOCK_SIZE, startPos.y + BLOCK_SIZE);
			if (classicColor)
			{
				for (int i = 0; i < 4; i++) //set size 30 x 30 and color
				{
					blocks[i].setFillColor(sf::Color::Blue);
				}
			}
			break;
		case Figure::S:
			blocks[0].setPosition(startPos.x, startPos.y + BLOCK_SIZE);
			blocks[1].setPosition(startPos.x + BLOCK_SIZE, startPos.y);
			blocks[2].setPosition(startPos.x + BLOCK_SIZE, startPos.y + BLOCK_SIZE);
			blocks[3].setPosition(startPos.x + 2 * BLOCK_SIZE, startPos.y);
			if (classicColor)
			{
				for (int i = 0; i < 4; i++) //set size 30 x 30 and color
				{
					blocks[i].setFillColor(sf::Color::Green);
				}
			}
			break;
		case Figure::Z:
			blocks[0].setPosition(startPos.x, startPos.y);
			blocks[1].setPosition(startPos.x + BLOCK_SIZE, startPos.y);
			blocks[2].setPosition(startPos.x + BLOCK_SIZE, startPos.y + BLOCK_SIZE);
			blocks[3].setPosition(startPos.x + 2 * BLOCK_SIZE, startPos.y + BLOCK_SIZE);
			if (classicColor)
			{
				for (int i = 0; i < 4; i++) //set size 30 x 30 and color
				{
					blocks[i].setFillColor(sf::Color::Red);
				}
			}
			break;
		}
	}

	void Figure::Rotate(bool clockwise)
	{
		if (_type_ != FigureType::O)
		{
			for (int i = 0; i < 4; i++)
			{
				sf::Vector2f VrelP, Vrot, Vprim;
				VrelP = gridCoords[i] - *pivot; //calculate coords of block V relative to pivot

				if (clockwise)//calculate coords of block V after rotation relative to pivot
				{
					Vrot = sf::Vector2f(-VrelP.y, VrelP.x); 
				}
				else
				{
					Vrot = sf::Vector2f(VrelP.y, -VrelP.x);
				}
				
				Vprim = Vrot + *pivot; //calculate coords of block V relative to grid

				gridCoords[i] = Vprim;

				if (gridCoords[i].x < 0) //check if block exceeded leftmost grid piece
				{
					float offsetX = -gridCoords[i].x; //calculate offset and move figure by the offset
					for (int j = 0; j < 4; j++)
					{
						gridCoords[j].x += offsetX;
						
					}
				}

				if (gridCoords[i].x > 9) //check if block exceeded rightmose grid piece
				{
					float offsetX = gridCoords[i].x - 9; //calculate offset and move figure by the offset
					for (int j = 0; j < 4; j++)
					{
						gridCoords[j].x -= offsetX;
					}
				}	

				if (gridCoords[i].y > 19)
				{
					float offsetY = gridCoords[i].y - 19;
					for (int j = 0; j < 4; j++)
					{
						gridCoords[j].y -= offsetY;
					}
				}
			}

			for (int i = 0; i < 4; i++) //set position on screen
			{
				blocks[i].setPosition(GRID_START_POS_X + gridCoords[i].x * BLOCK_SIZE, GRID_START_POS_Y + gridCoords[i].y * BLOCK_SIZE);
			}
		}	
	}

	void Figure::AddToGrid(short grid_X, short grid_Y)
	{
		switch (_type_) //set block coordinates on grid
		{
		case Figure::I:
			gridCoords[0] = sf::Vector2f(grid_X, grid_Y);
			gridCoords[1] = sf::Vector2f(grid_X + 1, grid_Y);
			gridCoords[2] = sf::Vector2f(grid_X + 2, grid_Y);
			gridCoords[3] = sf::Vector2f(grid_X + 3, grid_Y);

			pivot = &gridCoords[2]; //set pivot to rotate
			break;
		case Figure::T:
			gridCoords[0] = sf::Vector2f(grid_X, grid_Y + 1);
			gridCoords[1] = sf::Vector2f(grid_X + 1, grid_Y + 1);
			gridCoords[2] = sf::Vector2f(grid_X + 2, grid_Y + 1);
			gridCoords[3] = sf::Vector2f(grid_X + 1, grid_Y);

			pivot = &gridCoords[3];
			break;
		case Figure::O:
			gridCoords[0] = sf::Vector2f(grid_X, grid_Y);
			gridCoords[1] = sf::Vector2f(grid_X + 1, grid_Y);
			gridCoords[2] = sf::Vector2f(grid_X, grid_Y + 1);
			gridCoords[3] = sf::Vector2f(grid_X + 1, grid_Y + 1);

			pivot = nullptr; //O Figure has no pivot/no rotation
			break;
		case Figure::L:
			gridCoords[0] = sf::Vector2f(grid_X, grid_Y + 1);
			gridCoords[1] = sf::Vector2f(grid_X + 1, grid_Y + 1);
			gridCoords[2] = sf::Vector2f(grid_X + 2, grid_Y + 1);
			gridCoords[3] = sf::Vector2f(grid_X + 2, grid_Y);

			pivot = &gridCoords[1];
			break;
		case Figure::J:
			gridCoords[0] = sf::Vector2f(grid_X, grid_Y);
			gridCoords[1] = sf::Vector2f(grid_X, grid_Y + 1);
			gridCoords[2] = sf::Vector2f(grid_X + 1, grid_Y + 1);
			gridCoords[3] = sf::Vector2f(grid_X + 2, grid_Y + 1);

			pivot = &gridCoords[2];
			break;
		case Figure::S:
			gridCoords[0] = sf::Vector2f(grid_X, grid_Y + 1);
			gridCoords[1] = sf::Vector2f(grid_X + 1, grid_Y);
			gridCoords[2] = sf::Vector2f(grid_X + 1, grid_Y + 1);
			gridCoords[3] = sf::Vector2f(grid_X + 2, grid_Y);

			pivot = &gridCoords[2];
			break;
		case Figure::Z:
			gridCoords[0] = sf::Vector2f(grid_X, grid_Y);
			gridCoords[1] = sf::Vector2f(grid_X + 1, grid_Y);
			gridCoords[2] = sf::Vector2f(grid_X + 1, grid_Y + 1);
			gridCoords[3] = sf::Vector2f(grid_X + 2, grid_Y + 1);

			pivot = &gridCoords[2];
			break;
		}

	}

	Figure::FigureType GameState::randFigureType()
	{
		int roll = GameState::random(0, 6);
		Figure::FigureType currType = static_cast<Figure::FigureType>(roll);

		if (currType == lastType)
		{
			int reroll = GameState::random(0, 6);
			currType = static_cast<Figure::FigureType>(reroll);
		}
		return currType;
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
		currentFigure = Figure(static_cast<Figure::FigureType>(figure), sf::Vector2f(GRID_START_POS_X + 3 * BLOCK_SIZE, GRID_START_POS_Y), true);
		currentFigure.AddToGrid(3, 0);
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

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::X)
				{
					currentFigure.Rotate(true);				
				}
				else if (event.key.code == sf::Keyboard::Z)
				{
					currentFigure.Rotate(false);
				}

				if (event.key.code == sf::Keyboard::Right && !willGridExceed_X(1) && !willBlockOverlapBlock(1, 0)) //move right
				{
					for (int i = 0; i < 4; i++)
					{
						currentFigure.blocks[i].move(BLOCK_SIZE, 0); //move blocks to right by 30 
						currentFigure.gridCoords[i].x++; //set proper grid coords
					}
				}
				else if (event.key.code == sf::Keyboard::Left && !willGridExceed_X(-1) && !willBlockOverlapBlock(-1, 0)) //move left
				{
					for (int i = 0; i < 4; i++)
					{
						currentFigure.blocks[i].move(-BLOCK_SIZE, 0); //move blocks to left by 30 
						currentFigure.gridCoords[i].x--; //set proper grid coords
					}
				}
			}		
		}
	}

	void GameState::Update(float dt)
	{
		if (gameClock.getElapsedTime() >= sf::seconds(0.5) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) //Figure falling + fast fall
		{
			if (willGridExceed_Y(1) || willBlockOverlapBlock(0, 1))
			{
				for (int i = 0; i < 4; i++) //add to grid
				{
					grid[currentFigure.gridCoords[i].x][currentFigure.gridCoords[i].y] = std::make_pair(true, currentFigure.blocks[i]);
				}

				std::vector<int> filledRows = checkForRow();
				int rowsLost = 0; //how much rows got destroyed on 1 figure place
				if (filledRows.size() > 0)//if there is at least one row to destroy
				{
					for(int i = 0; i < filledRows.size(); i++) //iterates through destroyed rows Y indexes
					{
						for (int j = 0; j < 10; j++) //iterates through destroyed rows X indexes
						{
							for (int k = filledRows[i]; k > 0; k--) //move down all blocks from above deleted block
							{
								grid[j][k] = grid[j][k - 1];
								grid[j][k].second.setPosition(grid[j][k].second.getPosition().x, grid[j][k].second.getPosition().y + BLOCK_SIZE);
							}
						}
						rowsLost++;
						if (i != filledRows.size() - 1)
						{
							filledRows[i + 1] += rowsLost; //change next filled row index, cause all block above target were moved down
						}
					}		
				}

				lastType = currentFigure._type_;
				Figure::FigureType nextFigureType = randFigureType();

				sf::Vector2f startPos = sf::Vector2f(GRID_START_POS_X + 3 * BLOCK_SIZE, GRID_START_POS_Y);
				currentFigure = Figure(nextFigureType, startPos, true);
				
				for (int i = 0; i < 10; i++)
				{
					if (grid[i][0].first == true)
					{
						_data->window.close();
					}
				}

				currentFigure.AddToGrid(3, 0);
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					currentFigure.blocks[i].move(0, BLOCK_SIZE); //move blocks down by 30
					currentFigure.gridCoords[i].y++; //set proper grid coords
				}
			}	

			gameClock.restart();
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

	bool GameState::willBlockOverlapBlock(int offsetX, int offsetY)
	{
		for (int i = 0; i < 4; i++)
		{
			if (grid[currentFigure.gridCoords[i].x + offsetX][currentFigure.gridCoords[i].y + offsetY].first == true)
			{
				return true;
			}
		}
		return false;
	}

	bool GameState::willGridExceed_X(int offestX)
	{
		for (int i = 0; i < 4; i++)
		{
			if (currentFigure.gridCoords[i].x + offestX < 0 || currentFigure.gridCoords[i].x + offestX > 9)
			{
				return true;
			}
		}
		return false;
	}

	bool GameState::willGridExceed_Y(int offsetY)
	{
		for (int i = 0; i < 4; i++)
		{
			if (currentFigure.gridCoords[i].y + offsetY < 0 || currentFigure.gridCoords[i].y + offsetY > 19)
			{
				return true;
			}
		}
		return false;
	}

	std::vector<int> GameState::checkForRow() //returns indexes of filled rows
	{
		std::vector<int> filledRows;
		bool filled = true;

		for (int i = 19; i >= 0; i--) //iterates through grid Ys
		{
			filled = true;
			for (int j = 0; j < 10; j++) //iterates through grid Xs
			{
				if (grid[j][i].first == false) //if row is not filled -> skip i iteration
				{
					filled = false;
					break;
				}
			}
			if (filled)
			{
				filledRows.push_back(i);
			}
		}
		return filledRows;
	}

	int GameState::random(int min, int max)
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 gen(seed);
		std::uniform_int<int> distrib(min, max);
		return distrib(gen);
	}
}