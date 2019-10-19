#include "src/States/hpp/SettingsState.hpp"
#include "src/States/hpp/MenuState.hpp"
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
		_data->graphics.LoadFont("font", FONT_PATH);

		returnText.setFont(_data->graphics.GetFont("font"));
		returnText.setCharacterSize(50);
		returnText.setString("Return");

		originalColorText.setFont(_data->graphics.GetFont("font"));
		originalColorText.setCharacterSize(50);
		originalColorText.setString("Original Colors: ON");

		drawFullGridText.setFont(_data->graphics.GetFont("font"));
		drawFullGridText.setCharacterSize(50);
		drawFullGridText.setString("Draw Full Grid: ON");


		
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
}