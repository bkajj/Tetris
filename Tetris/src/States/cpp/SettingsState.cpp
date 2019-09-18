#include "src/States/hpp/SettingsState.hpp"
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

		}
	}

	void SettingsState::Update(float dt)
	{

	}

	void SettingsState::Draw(float dt)
	{
		_data->window.clear();

		_data->window.display();
	}
}