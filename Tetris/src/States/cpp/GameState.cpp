#include "src/States/hpp/GameState.hpp"
#include "src/GameEngine/hpp/Game.hpp"
#include "src/States/hpp/GameOverState.hpp"
#include "src/DEFINE.hpp"
#include <iostream>
#include <chrono>
#include <random>
#include <map>

namespace hgw
{
#pragma region Figure
	Figure::Figure()
	{

	}

	void Figure::Init(Figure::FigureType type, sf::Vector2f startCoords, bool classicColor = true, bool isGhostPiece = false)
	{
		setOffsetData();

		_type_ = I;

		switch (_type_) //set block coordinates on grid
		{
		case Figure::I:
			gridCoords[0] = sf::Vector2f(startCoords.x, startCoords.y);
			gridCoords[1] = sf::Vector2f(startCoords.x + 1, startCoords.y);
			gridCoords[2] = sf::Vector2f(startCoords.x + 2, startCoords.y);
			gridCoords[3] = sf::Vector2f(startCoords.x + 3, startCoords.y);

			pivot = &gridCoords[1]; //set pivot to rotate

			if (classicColor) //set color
			{
				setColor(sf::Color::Cyan);
			}
			break;
		case Figure::T:
			gridCoords[0] = sf::Vector2f(startCoords.x, startCoords.y + 1);
			gridCoords[1] = sf::Vector2f(startCoords.x + 1, startCoords.y + 1);
			gridCoords[2] = sf::Vector2f(startCoords.x + 2, startCoords.y + 1);
			gridCoords[3] = sf::Vector2f(startCoords.x + 1, startCoords.y);

			pivot = &gridCoords[3];

			if (classicColor)
			{
				setColor(sf::Color(128, 0, 128, 255));//purple
			}
			break;
		case Figure::O:
			gridCoords[0] = sf::Vector2f(startCoords.x, startCoords.y);
			gridCoords[1] = sf::Vector2f(startCoords.x + 1, startCoords.y);
			gridCoords[2] = sf::Vector2f(startCoords.x, startCoords.y + 1);
			gridCoords[3] = sf::Vector2f(startCoords.x + 1, startCoords.y + 1);

			pivot = nullptr; //O Figure has no pivot/no rotation

			if (classicColor)
			{
				setColor(sf::Color::Yellow);
			}
			break;
		case Figure::L:
			gridCoords[0] = sf::Vector2f(startCoords.x, startCoords.y + 1);
			gridCoords[1] = sf::Vector2f(startCoords.x + 1, startCoords.y + 1);
			gridCoords[2] = sf::Vector2f(startCoords.x + 2, startCoords.y + 1);
			gridCoords[3] = sf::Vector2f(startCoords.x + 2, startCoords.y);

			pivot = &gridCoords[1];

			if (classicColor)
			{
				setColor(sf::Color(255, 165, 0, 255)); //orange
			}
			break;
		case Figure::J:
			gridCoords[0] = sf::Vector2f(startCoords.x, startCoords.y);
			gridCoords[1] = sf::Vector2f(startCoords.x, startCoords.y + 1);
			gridCoords[2] = sf::Vector2f(startCoords.x + 1, startCoords.y + 1);
			gridCoords[3] = sf::Vector2f(startCoords.x + 2, startCoords.y + 1);

			pivot = &gridCoords[2];

			if (classicColor)
			{
				setColor(sf::Color::Blue);
			}
			break;
		case Figure::S:
			gridCoords[0] = sf::Vector2f(startCoords.x, startCoords.y + 1);
			gridCoords[1] = sf::Vector2f(startCoords.x + 1, startCoords.y);
			gridCoords[2] = sf::Vector2f(startCoords.x + 1, startCoords.y + 1);
			gridCoords[3] = sf::Vector2f(startCoords.x + 2, startCoords.y);

			pivot = &gridCoords[2];

			if (classicColor)
			{
				setColor(sf::Color::Green);
			}
			break;
		case Figure::Z:
			gridCoords[0] = sf::Vector2f(startCoords.x, startCoords.y);
			gridCoords[1] = sf::Vector2f(startCoords.x + 1, startCoords.y);
			gridCoords[2] = sf::Vector2f(startCoords.x + 1, startCoords.y + 1);
			gridCoords[3] = sf::Vector2f(startCoords.x + 2, startCoords.y + 1);

			pivot = &gridCoords[2];

			if (classicColor)
			{
				setColor(sf::Color::Red);
			}
			break;
		}

		if (!classicColor) //set random color if enabled
		{
			setColor(sf::Color(GameState::random(0, 255), GameState::random(0, 255), GameState::random(0, 255), 255));
		}


		for (int i = 0; i < 4; i++)
		{
			blocks[i].setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));

			blocks[i].setPosition(GRID_START_POS_X + gridCoords[i].x * BLOCK_SIZE,
				GRID_START_POS_Y + gridCoords[i].y * BLOCK_SIZE);
		}

	}

	void Figure::setColor(sf::Color color)
	{
		figureColor = color;
		for (int i = 0; i < 4; i++)
		{
			blocks[i].setFillColor(color);
		}
	}

	void Figure::updateGhostCoords()
	{
		gridCoords = GameState::currentFigure.gridCoords;
		for (int i = 0; i < 4; i++)
		{
			blocks[i].setPosition(GameState::currentFigure.blocks[i].getPosition());
		}

		while (!willGridExceed_X(0) && !willGridExceed_Y(0) && !willBlockOverlapBlock(0, 0))
		{
			moveFigure(sf::Vector2f(0, 1));
		}
		moveFigure(sf::Vector2f(0, -1));
	}

	void Figure::instaPlace()
	{
		for (int i = 0; i < 4; i++)
		{
			GameState::currentFigure.blocks[i].setPosition(GameState::ghostFigure.blocks[i].getPosition());
			GameState::currentFigure.gridCoords[i] = GameState::ghostFigure.gridCoords[i];
		}
	}

	void Figure::Rotate(bool clockwise, bool shouldOffest)
	{
		if (_type_ != FigureType::O)
		{
			int oldRotationState = rotationState;

			if (clockwise) rotationState++;
			else rotationState--;

			rotationState = GameState::negMod(rotationState);

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
			}

			if (shouldOffest)
			{
				bool canOffset = testRotationOffset(oldRotationState, rotationState);

				if (!canOffset)
				{
					Rotate(!clockwise, false);
				}
			}	
		}
	}

	void Figure::moveFigure(sf::Vector2f offset)
	{
		for (int i = 0; i < 4; i++)
		{
			gridCoords[i] += offset;
			blocks[i].move(offset.x * BLOCK_SIZE, offset.y * BLOCK_SIZE);
		}
	}

	bool Figure::willBlockOverlapBlock(float offsetX, float offsetY)
	{
		for (int i = 0; i < 4; i++)
		{
			if (GameState::grid[to_uns(gridCoords[i].x + offsetX)][to_uns(gridCoords[i].y + offsetY)].first == true)
			{
				return true;
			}
		}
		return false;
	}

	bool Figure::willGridExceed_X(float offestX)
	{
		for (int i = 0; i < 4; i++)
		{
			if (gridCoords[i].x + offestX < 0 || gridCoords[i].x + offestX > 9)
			{
				return true;
			}
		}
		return false;
	}

	bool Figure::willGridExceed_Y(float offsetY)
	{
		for (int i = 0; i < 4; i++)
		{
			if (gridCoords[i].y + offsetY < 0 || gridCoords[i].y + offsetY > 19)
			{
				return true;
			}
		}
		return false;
	}

	void Figure::setOffsetData()
	{
		JLSTZ_offsetData[std::make_pair(0, 0)] = sf::Vector2f(0, 0);
		JLSTZ_offsetData[std::make_pair(0, 1)] = sf::Vector2f(0, 0);
		JLSTZ_offsetData[std::make_pair(0, 2)] = sf::Vector2f(0, 0);
		JLSTZ_offsetData[std::make_pair(0, 3)] = sf::Vector2f(0, 0);

		JLSTZ_offsetData[std::make_pair(1, 0)] = sf::Vector2f(0, 0);
		JLSTZ_offsetData[std::make_pair(1, 1)] = sf::Vector2f(1, 0);
		JLSTZ_offsetData[std::make_pair(1, 2)] = sf::Vector2f(0, 0);
		JLSTZ_offsetData[std::make_pair(1, 3)] = sf::Vector2f(-1, 0);

		JLSTZ_offsetData[std::make_pair(2, 0)] = sf::Vector2f(0, 0);
		JLSTZ_offsetData[std::make_pair(2, 1)] = sf::Vector2f(1, -1);
		JLSTZ_offsetData[std::make_pair(2, 2)] = sf::Vector2f(0, 0);
		JLSTZ_offsetData[std::make_pair(2, 3)] = sf::Vector2f(-1, -1);

		JLSTZ_offsetData[std::make_pair(3, 0)] = sf::Vector2f(0, 0);
		JLSTZ_offsetData[std::make_pair(3, 1)] = sf::Vector2f(0, 2);
		JLSTZ_offsetData[std::make_pair(3, 2)] = sf::Vector2f(0, 0);
		JLSTZ_offsetData[std::make_pair(3, 3)] = sf::Vector2f(0, 2);

		JLSTZ_offsetData[std::make_pair(4, 0)] = sf::Vector2f(0, 0);
		JLSTZ_offsetData[std::make_pair(4, 1)] = sf::Vector2f(1, 2);
		JLSTZ_offsetData[std::make_pair(4, 2)] = sf::Vector2f(0, 0);
		JLSTZ_offsetData[std::make_pair(4, 3)] = sf::Vector2f(-1, 2);


		I_offsetData[std::make_pair(0, 0)] = sf::Vector2f(0, 0);
		I_offsetData[std::make_pair(0, 1)] = sf::Vector2f(-1, 0);
		I_offsetData[std::make_pair(0, 2)] = sf::Vector2f(-1, 1);
		I_offsetData[std::make_pair(0, 3)] = sf::Vector2f(0, 1);

		I_offsetData[std::make_pair(1, 0)] = sf::Vector2f(-1, 0);
		I_offsetData[std::make_pair(1, 1)] = sf::Vector2f(0, 0);
		I_offsetData[std::make_pair(1, 2)] = sf::Vector2f(1, 1);
		I_offsetData[std::make_pair(1, 3)] = sf::Vector2f(0, 1);

		I_offsetData[std::make_pair(2, 0)] = sf::Vector2f(2, 0);
		I_offsetData[std::make_pair(2, 1)] = sf::Vector2f(0, 0);
		I_offsetData[std::make_pair(2, 2)] = sf::Vector2f(-2, 1);
		I_offsetData[std::make_pair(2, 3)] = sf::Vector2f(0, 1);

		I_offsetData[std::make_pair(3, 0)] = sf::Vector2f(-1, 0);
		I_offsetData[std::make_pair(3, 1)] = sf::Vector2f(0, 1);
		I_offsetData[std::make_pair(3, 2)] = sf::Vector2f(1, 0);
		I_offsetData[std::make_pair(3, 3)] = sf::Vector2f(0, -1);

		I_offsetData[std::make_pair(4, 0)] = sf::Vector2f(2, 0);
		I_offsetData[std::make_pair(4, 1)] = sf::Vector2f(0, -2);
		I_offsetData[std::make_pair(4, 2)] = sf::Vector2f(-2, 0);
		I_offsetData[std::make_pair(4, 3)] = sf::Vector2f(0, 2);
	}

	bool Figure::testRotationOffset(int oldRotationState, int newRotationState)
	{
		std::map<std::pair<int, int>, sf::Vector2f>* currOffsetData;

		sf::Vector2f offsetVal1, offsetVal2;
		sf::Vector2f endOffset = sf::Vector2f(0, 0);
		bool isMovePossible = false;

		if (_type_ == FigureType::I)
		{
			currOffsetData = &I_offsetData;
		}
		else
		{
			currOffsetData = &JLSTZ_offsetData;
		}

		for (int i = 0; i < 4; i++)
		{
			offsetVal1 = (*currOffsetData)[std::make_pair(i, oldRotationState)];
			offsetVal2 = (*currOffsetData)[std::make_pair(i, newRotationState)];
			endOffset = offsetVal1 - offsetVal2;

			if (!willGridExceed_X(endOffset.x) && !willGridExceed_Y(endOffset.y) &&
				!willBlockOverlapBlock(endOffset.x, endOffset.y)) //if move possible
			{
				isMovePossible = true;
				break;
			}
		}

		for (int i = 0; i < 4; i++) //set position on screen
		{
			blocks[i].setPosition(GRID_START_POS_X + gridCoords[i].x * BLOCK_SIZE, GRID_START_POS_Y + gridCoords[i].y * BLOCK_SIZE);
		}

		if (isMovePossible)
		{
			moveFigure(endOffset);
		}
		return isMovePossible;
	}

	bool Figure::areCoordsGood()
	{
		for (int i = 0; i < 4; i++)
		{
			if (gridCoords[i].x < 0 || gridCoords[i].x > 9 || 
				gridCoords[i].y < 0 || gridCoords[i].y > 19)
			{
				return false;
			}
		}
		return true;
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
#pragma endregion

#pragma region GameState
	GameState::GameState(GameDataRef data)
	{
		_data = data;
	}

	void GameState::Init()
	{
		for (int i = 0; i < 11; i++) //draw a grid
		{
			verticalLines[i].setSize(sf::Vector2f(1, 600));
			verticalLines[i].setPosition(sf::Vector2f(static_cast<float>(APP_WIDTH / 2 + i * 30 - 150), 100));
		}
		for (int i = 0; i < 21; i++)
		{
			horizontalLines[i].setSize(sf::Vector2f(300, 1));
			horizontalLines[i].setPosition(verticalLines[0].getPosition().x, verticalLines[0].getPosition().y + i * 30);
		}

		gameClock.restart(); //start clock that moves blocks

		Figure::FigureType figure = randFigureType();

		currentFigure.Init(figure, sf::Vector2f(3, 0), true, false);

		ghostFigure.Init(figure, sf::Vector2f(3, 0), true, true);
		ghostFigure.setColor(sf::Color(currentFigure.figureColor.r, currentFigure.figureColor.g,
									   currentFigure.figureColor.b, currentFigure.figureColor.a - 175));
		ghostFigure.updateGhostCoords();
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
				if (event.key.code == sf::Keyboard::Space)
				{
					//insta place with rotation causes errors
					Figure::instaPlace();
					//!!!! array subscript out of range somehere here // probably not not
					if (currentFigure.areCoordsGood())
					{
						for (int i = 0; i < 4; i++) //add to grid
						{
							grid[to_uns(currentFigure.gridCoords[i].x)][to_uns(currentFigure.gridCoords[i].y)] = std::make_pair(true, currentFigure.blocks[i]);
						}
					}

					destroyFilledRows(); //clear lines
					setNextFigure(true);

					for (int i = 0; i < 10; i++) //check for lose condition
					{
						if (grid[i][0].first == true)
						{
							//clear grid
							for (int i = 0; i < 10; i++)
							{
								for (int j = 0; j < 20; j++)
								{
									grid[i][j] = std::make_pair(false, sf::RectangleShape());
								}
							}

							_data->machine.AddState(StateRef(new GameOverState(_data)));
						}
					}
				}
				else if (event.key.code == sf::Keyboard::X)
				{
					currentFigure.Rotate(true, true);
					ghostFigure.updateGhostCoords();
				}
				else if (event.key.code == sf::Keyboard::Z)
				{
					currentFigure.Rotate(false, true);
					ghostFigure.updateGhostCoords();
				}			
				else if (event.key.code == sf::Keyboard::Right && !currentFigure.willGridExceed_X(1) && !currentFigure.willBlockOverlapBlock(1, 0)) //move right
				{
					currentFigure.moveFigure(sf::Vector2f(1, 0));
					ghostFigure.moveFigure(sf::Vector2f(1, 0));
					ghostFigure.updateGhostCoords();
				}
				else if (event.key.code == sf::Keyboard::Left && !currentFigure.willGridExceed_X(-1) && !currentFigure.willBlockOverlapBlock(-1, 0)) //move left
				{
					currentFigure.moveFigure(sf::Vector2f(-1, 0));
					ghostFigure.moveFigure(sf::Vector2f(-1, 0));
					ghostFigure.updateGhostCoords();
				}
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down)
			{
				isDownKeyPressed = false;
			}
		}
	}

	void GameState::Update(float dt)
	{
		if ((gameClock.getElapsedTime() >= sf::seconds(0.5) || 
			(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !isDownKeyPressed))) //Figure falling + fast fall
		{
			if (currentFigure.willGridExceed_Y(1) || currentFigure.willBlockOverlapBlock(0, 1))
			{
				//!!!! array subscript out of range somehere here // probably not not
				if (currentFigure.areCoordsGood())
				{
					for (int i = 0; i < 4; i++) //add to grid
					{
						grid[to_uns(currentFigure.gridCoords[i].x)][to_uns(currentFigure.gridCoords[i].y)] = std::make_pair(true, currentFigure.blocks[i]);
					}
				}
		
				destroyFilledRows(); //clear lines
				setNextFigure(true);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					isDownKeyPressed = true;
				}
				else
				{
					isDownKeyPressed = false;
				}

				for (int i = 0; i < 10; i++) //check for lose condition
				{
					if (grid[i][0].first == true)
					{
						//clear grid
						for (int i = 0; i < 10; i++)
						{
							for (int j = 0; j < 20; j++)
							{
								grid[i][j] = std::make_pair(false, sf::RectangleShape());
							}
						}

						_data->machine.AddState(StateRef(new GameOverState(_data)));
					}
				}
			}
			else
			{
				currentFigure.moveFigure(sf::Vector2f(0, 1));
			}
			gameClock.restart();
		}
	}

	void GameState::Draw(float dt)
	{
		_data->window.clear();

		for (int i = 0; i < 4; i++) //draw current figure and ghost figure
		{
			_data->window.draw(currentFigure.blocks[i]);
			_data->window.draw(ghostFigure.blocks[i]);
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

		//_data->window.draw(verticalLines[0]);
		//_data->window.draw(verticalLines[10]);

		//_data->window.draw(horizontalLines[0]);
		//_data->window.draw(horizontalLines[20]);

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

	void GameState::destroyFilledRows()
	{
		std::vector<int> filledRows = checkForRow();
		int rowsLost = 0; //how much rows got destroyed on 1 figure place
		if (filledRows.size() > 0)//if there is at least one row to destroy
		{
			for (int i = 0; i < filledRows.size(); i++) //iterates through destroyed rows Y indexes
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
		unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
		std::mt19937 gen(seed);
		std::uniform_int<int> distrib(min, max);
		return distrib(gen);
	}

	int GameState::negMod(int val)
	{
		if (val < 0)
		{
			return val % 4 + 4;
		}
		return val % 4;
	}

	void GameState::setNextFigure(bool classicColor)
	{
		lastType = currentFigure._type_;
		Figure::FigureType nextFigureType = randFigureType();

		currentFigure.Init(nextFigureType, sf::Vector2f(3, 0), classicColor, false);

		ghostFigure.Init(nextFigureType, sf::Vector2f(3, 0), classicColor, true);
		ghostFigure.setColor(sf::Color(currentFigure.figureColor.r, currentFigure.figureColor.g,
			currentFigure.figureColor.b, currentFigure.figureColor.a - 175));
		ghostFigure.updateGhostCoords();
	}

#pragma endregion

	//static variables
	std::map<std::pair<int, int>, sf::Vector2f> Figure::I_offsetData;
	std::map<std::pair<int, int>, sf::Vector2f> Figure::JLSTZ_offsetData;

	std::array<std::array<std::pair<bool, sf::RectangleShape>, 20>, 10> GameState::grid;

	Figure GameState::currentFigure;
	Figure GameState::ghostFigure;
	Figure::FigureType GameState::lastType;
}