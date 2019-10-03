#include "src\States\hpp\GameOverState.hpp"
#include "src\States\hpp\GameState.hpp"
#include "src\States\hpp\MenuState.hpp"
#include "src\States\hpp\SettingsState.hpp"
#include "src\DEFINE.hpp"

namespace hgw
{
	GameOverState::GameOverState(GameDataRef _data)
	{
		this->_data = _data;
	}

	void GameOverState::Init()
	{
		_data->graphics.LoadFont("font", FONT_PATH);

		gameOverText.setFont(_data->graphics.GetFont("font"));
		restartText.setFont(_data->graphics.GetFont("font"));
		settingsText.setFont(_data->graphics.GetFont("font"));
		exitText.setFont(_data->graphics.GetFont("font"));

		gameOverText.setString("GAME OVER");
		gameOverText.setCharacterSize(160);

		restartText.setString("START");
		restartText.setCharacterSize(100);

		settingsText.setString("SETTINGS");
		settingsText.setCharacterSize(100);

		exitText.setString("EXIT");
		exitText.setCharacterSize(100);

		gameOverText.setPosition((APP_WIDTH - gameOverText.getGlobalBounds().width) / 2 - 15,
								 (APP_HEIGHT - gameOverText.getGlobalBounds().height) / 10);

		restartText.setPosition((APP_WIDTH - restartText.getGlobalBounds().width) / 2, gameOverText.getPosition().y + 250);
		settingsText.setPosition((APP_WIDTH - settingsText.getGlobalBounds().width) / 2, restartText.getPosition().y + 100);
		exitText.setPosition((APP_WIDTH - exitText.getGlobalBounds().width) / 2, settingsText.getPosition().y + 100);
	}

	void GameOverState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}
			else if (_data->input.IsTextClicked(restartText, sf::Mouse::Left, event.type, _data->window))
			{
				_data->machine.AddState(StateRef(new GameState(_data)));
			}
			else if (_data->input.IsTextClicked(settingsText, sf::Mouse::Left, event.type, _data->window))
			{
				_data->machine.AddState(StateRef(new SettingsState(_data)));
			}
			else if (_data->input.IsTextClicked(exitText, sf::Mouse::Left, event.type, _data->window))
			{
				_data->window.close();
			}
		}
	}

	void GameOverState::Update(float dt)
	{

	}

	void GameOverState::Draw(float dt)
	{
		_data->window.clear();

		_data->window.draw(gameOverText);
		_data->window.draw(restartText);
		_data->window.draw(settingsText);
		_data->window.draw(exitText);

		_data->window.display();
	}
}