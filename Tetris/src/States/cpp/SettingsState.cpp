#include "src/States/hpp/SettingsState.hpp"
#include "src/States/hpp/MenuState.hpp"
#include "src/States/hpp/GameState.hpp"
#include "src/GameEngine/hpp/Game.hpp"
#include "src/DEFINE.hpp"
#include <iostream>

namespace hgw
{
	SettingsState::SettingsState(GameDataRef _data)
	{
		this->_data = _data;
	}

	void SettingsState::Init()
	{
		bool state;
		_data->graphics.LoadFont("font", FONT_PATH);

		returnText.setFont(_data->graphics.GetFont("font"));
		returnText.setCharacterSize(50);
		returnText.setString("Return");

		//ADD FUNCTION TO LOAD ALL VARIABLES FROM FILE AND SET GAME VARIABLES

		originalColorText.setFont(_data->graphics.GetFont("font"));
		originalColorText.setCharacterSize(50);
		setTextString(GameData::variableNames::originalColors);

		drawFullGridText.setFont(_data->graphics.GetFont("font"));
		drawFullGridText.setCharacterSize(50);
		setTextString(GameData::variableNames::fullGrid);
		
		returnText.setPosition((APP_WIDTH - returnText.getGlobalBounds().width) / 2, 800);
		originalColorText.setPosition((APP_WIDTH - originalColorText.getGlobalBounds().width) / 2, 100);
		drawFullGridText.setPosition((APP_WIDTH - drawFullGridText.getGlobalBounds().width) / 2, 160);
	}

	void SettingsState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}

			if (_data->input.IsTextClicked(returnText, sf::Mouse::Left, event.type, _data->window))
			{
				_data->machine.AddState(StateRef(new MenuState(_data)));
			}

			if (_data->input.IsTextClicked(drawFullGridText, sf::Mouse::Left, event.type, _data->window))
			{
				GameState::updateGameData(GameData::variableNames::fullGrid, !_data->saveVariables.fullGrid, _data);

				setTextString(GameData::variableNames::fullGrid);
			}

			if (_data->input.IsTextClicked(originalColorText, sf::Mouse::Left, event.type, _data->window))
			{
				GameState::updateGameData(GameData::variableNames::originalColors, !_data->saveVariables.originalColors, _data);

				setTextString(GameData::variableNames::originalColors);
			}
		}
	}

	void SettingsState::Update(float dt)
	{

	}

	void SettingsState::Draw(float dt)
	{
		_data->window.clear();

		_data->window.draw(returnText);
		_data->window.draw(originalColorText);
		_data->window.draw(drawFullGridText);

		_data->window.display();
	}

	void SettingsState::setTextString(GameData::variableNames variableName)
	{
		switch (variableName)
		{
		case hgw::GameData::fullGrid:
			if (_data->saveVariables.fullGrid)
			{
				drawFullGridText.setString("Draw Full Grid: ON");
			}
			else
			{
				drawFullGridText.setString("Draw Full Grid: OFF");
			}
			break;

		case hgw::GameData::originalColors:

			if (_data->saveVariables.originalColors)
			{
				originalColorText.setString("Original Colors: ON");
			}
			else
			{
				originalColorText.setString("Original Colors: OFF");
			}
		}
	}
}