#include "src/States/hpp/SettingsState.hpp"
#include "src/States/hpp/MenuState.hpp"
#include "src/States/hpp/GameState.hpp"
#include "src/GameEngine/hpp/Game.hpp"
#include "src/GameEngine/hpp/Components.hpp"
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
		_data->graphics.LoadFont("font", FONT_PATH);

		returnText.setFont(_data->graphics.GetFont("font"));
		returnText.setCharacterSize(50);
		returnText.setString("Return");

		_data->graphics.LoadTexture("sound off", SOUND_OFF_FILEPATH);
		_data->graphics.LoadTexture("sound on", SOUND_ON_FILEPATH);
		_data->graphics.LoadTexture("music off", MUSIC_OFF_FILEPATH);
		_data->graphics.LoadTexture("music on", MUSIC_ON_FILEPATH);

		soundBar.Init(_data);
		musicBar.Init(_data);

		soundOff.setTexture(_data->graphics.GetTexture("sound off"));
		soundOn.setTexture(_data->graphics.GetTexture("sound on"));

		musicOff.setTexture(_data->graphics.GetTexture("music off"));
		musicOn.setTexture(_data->graphics.GetTexture("music on"));

		soundOff.setScale(0.7, 0.7);
		soundOn.setScale(0.7, 0.7);
		musicOff.setScale(0.7, 0.7);
		musicOn.setScale(0.7, 0.7);

		originalColorText.setFont(_data->graphics.GetFont("font"));
		originalColorText.setCharacterSize(50);
		setTextString(GameData::variableNames::originalColors);

		drawFullGridText.setFont(_data->graphics.GetFont("font"));
		drawFullGridText.setCharacterSize(50);
		setTextString(GameData::variableNames::fullGrid);
		
		returnText.setPosition((APP_WIDTH - returnText.getGlobalBounds().width) / 2, 800);
		originalColorText.setPosition((APP_WIDTH - originalColorText.getGlobalBounds().width) / 2, 180);
		drawFullGridText.setPosition((APP_WIDTH - drawFullGridText.getGlobalBounds().width) / 2, 230);

		soundOff.setPosition((APP_WIDTH - soundOff.getGlobalBounds().width) / 5 + 70, 100);
		soundOn.setPosition((APP_WIDTH - soundOn.getGlobalBounds().width) / 5 + 70, 100);
		
		musicOff.setPosition(soundOff.getPosition().x + drawFullGridText.getGlobalBounds().width - 170, 50);
		musicOn.setPosition(soundOff.getPosition().x + drawFullGridText.getGlobalBounds().width - 170, 50);

		musicBar.Attach(musicOff, sf::Vector2f(0, -musicOn.getGlobalBounds().height - 10), musicVolume);
		soundBar.Attach(soundOff, sf::Vector2f(0, -soundOn.getGlobalBounds().height - 10), soundVolume);
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

		_data->window.draw(soundOff);
		_data->window.draw(soundOn);
		_data->window.draw(musicOff);
		_data->window.draw(musicOn);

		_data->window.draw(musicBar._bar);
		_data->window.draw(musicBar._point);
		_data->window.draw(soundBar._bar);
		_data->window.draw(soundBar._point);

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