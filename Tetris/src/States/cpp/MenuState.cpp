#include "src/States/hpp/MenuState.hpp"
#include "src/States/hpp/SettingsState.hpp"
#include "src/States/hpp/GameState.hpp"
#include "src/GameEngine/hpp/Game.hpp"
#include "src/DEFINE.hpp"
#include <iostream>
#include <fstream>
#include <string>

namespace hgw
{
	MenuState::MenuState(GameDataRef _data)
	{
		this->_data = _data;
	}

	void MenuState::Init()
	{
		_data->gameData.gameData = SaveGameData(1, true, false, 0.5f, 0.8f);
		_data->gameData.serializeSave();


		_data->graphics.LoadFont("font", FONT_PATH);

		tetrisText.setFont(_data->graphics.GetFont("font"));
		startText.setFont(_data->graphics.GetFont("font"));
		settingsText.setFont(_data->graphics.GetFont("font"));
		exitText.setFont(_data->graphics.GetFont("font"));

		tetrisText.setString("TETRIS");
		tetrisText.setCharacterSize(200);

		startText.setString("START");
		startText.setCharacterSize(100);

		settingsText.setString("SETTINGS");
		settingsText.setCharacterSize(100);

		exitText.setString("EXIT");
		exitText.setCharacterSize(100);

		tetrisText.setPosition(sf::Vector2f((APP_WIDTH - tetrisText.getLocalBounds().width) / 2 - 15, 30));
		startText.setPosition(sf::Vector2f((APP_WIDTH - startText.getLocalBounds().width) / 2, tetrisText.getPosition().y + 350));
		settingsText.setPosition(sf::Vector2f((APP_WIDTH - settingsText.getLocalBounds().width) / 2, startText.getPosition().y + 100));
		exitText.setPosition(sf::Vector2f((APP_WIDTH - exitText.getLocalBounds().width) / 2, settingsText.getPosition().y + 100));

		loadAllVariablesFromFile();
	}

	void MenuState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}

			if (_data->input.IsTextClicked(startText, sf::Mouse::Button::Left, event.type, _data->window))
			{
				_data->machine.AddState(StateRef(new GameState(_data)));
			}

			if (_data->input.IsTextClicked(settingsText, sf::Mouse::Button::Left, event.type, _data->window))
			{
				_data->machine.AddState(StateRef(new SettingsState(_data)));
			}

			if (_data->input.IsTextClicked(exitText, sf::Mouse::Button::Left, event.type, _data->window))
			{
				_data->window.close();
			}

		}
		
	}

	void MenuState::Update(float dt)
	{

	}

	void MenuState::Draw(float dt)
	{
		_data->window.clear();

		_data->window.draw(tetrisText);
		_data->window.draw(startText);
		_data->window.draw(settingsText);
		_data->window.draw(exitText);

		_data->window.display();	
	}

	void MenuState::loadAllVariablesFromFile()
	{
		dataFile.open("data.dat", std::fstream::in);

		if (dataFile.good())
		{
			std::string line;
			while (std::getline(dataFile, line))
			{
				unsigned int spacePos = line.find(" ");

				std::string varName = line.substr(0, spacePos);
				std::string varValue = line.substr(spacePos, line.size() - spacePos);

				if (varName == "highscore")
				{
					_data->saveVariables.highScore = std::stoi(varValue);
				}
				else if (varName == "fullgrid")
				{
					_data->saveVariables.fullGrid = std::stoi(varValue);
				}
				if (varName == "originalcolors")
				{
					_data->saveVariables.originalColors = std::stoi(varValue);
				}
			}
		}

		dataFile.close();
	}
}