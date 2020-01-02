#include "src/States/hpp/ConnectState.hpp"
#include "src/DEFINE.hpp"
#include <iostream>
#include <SFML/Network.hpp>

namespace hgw
{
	ConnectState::ConnectState(GameDataRef _data)
	{
		this->_data = _data;
	}

	void ConnectState::Init()
	{
		_data->graphics.LoadFont("font", FONT_PATH);
		sf::Font &font = _data->graphics.GetFont("font");

		createGameText.setString("CREATE GAME");
		createGameText.setFont(font);
		createGameText.setCharacterSize(50);

		joinGameText.setString("JOIN GAME");
		joinGameText.setFont(font);
		joinGameText.setCharacterSize(50);

		localIPText.setString("Your IP: " + sf::IpAddress::getPublicAddress().toString());
		localIPText.setFont(font);
		localIPText.setCharacterSize(50);

		toConnectText.setString("IP TO CONNECT TO:\n   ___.___._._");
		toConnectText.setFont(font);
		toConnectText.setCharacterSize(50);

		waitingForConnectionText.setString("WAITING FOR CONNECTION...");
		waitingForConnectionText.setFont(font);
		waitingForConnectionText.setCharacterSize(50);

		createGameText.setPosition((APP_WIDTH - createGameText.getGlobalBounds().width) / 2, 300);
		joinGameText.setPosition((APP_WIDTH - joinGameText.getGlobalBounds().width) / 2, createGameText.getPosition().y + 100);
		localIPText.setPosition((APP_WIDTH - localIPText.getGlobalBounds().width) / 2, 150);

		toConnectText.setPosition((APP_WIDTH - toConnectText.getGlobalBounds().width) / 2, 225);
		waitingForConnectionText.setPosition((APP_WIDTH - toConnectText.getGlobalBounds().width) / 2, 225);
	}

	void ConnectState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				_data->window.close();
			}
			else if (_data->input.IsTextClicked(createGameText, sf::Mouse::Left, event.type, _data->window))
			{
				isCreatingGame = true;

				if (server.listen(server.AnyPort) != sf::Socket::Done)
				{
					std::cout << "Error Ocurred while listening to " << server.getLocalPort() << std::endl;
				}

				if (server.accept(client) != sf::Socket::Done)
				{
					std::cout << "Error Ocurred while connecting to client" << std::endl;
				}
			}
			else if (_data->input.IsTextClicked(joinGameText, sf::Mouse::Left, event.type, _data->window))
			{
				isJoiningGame = true;

				if (socket.connect(ipToConnectTo, 53000) != sf::Socket::Done)
				{
					std::cout << "Error Ocurred while connecting to server (" << ipToConnectTo << ")" << std::endl;
				}
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (isJoiningGame)
				{
					if ((event.key.code == sf::Keyboard::BackSpace || event.key.code == sf::Keyboard::Backspace) && ipDigitsEntered.size() > 0) //removing ip digit
					{
						ipDigitsEntered.erase(ipDigitsEntered.end() - 1);
						toConnectText.setString("IP TO CONNECT TO:\n   " + strigToIP(ipDigitsEntered));
					}
					else if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return) //joining game
					{
						//TODO
					}
					else if (ipDigitsEntered.size() < 8) //adding ip digit
					{
						char keyPressed = 'Q';

						switch (event.key.code)
						{
						case sf::Keyboard::Num0:
						case sf::Keyboard::Numpad0:
							keyPressed = '0';
							break;

						case sf::Keyboard::Num1:
						case sf::Keyboard::Numpad1:
							keyPressed = '1';
							break;

						case sf::Keyboard::Num2:
						case sf::Keyboard::Numpad2:
							keyPressed = '2';
							break;

						case sf::Keyboard::Num3:
						case sf::Keyboard::Numpad3:
							keyPressed = '3';
							break;

						case sf::Keyboard::Num4:
						case sf::Keyboard::Numpad4:
							keyPressed = '4';
							break;

						case sf::Keyboard::Num5:
						case sf::Keyboard::Numpad5:
							keyPressed = '5';
							break;

						case sf::Keyboard::Num6:
						case sf::Keyboard::Numpad6:
							keyPressed = '6';
							break;

						case sf::Keyboard::Num7:
						case sf::Keyboard::Numpad7:
							keyPressed = '7';
							break;

						case sf::Keyboard::Num8:
						case sf::Keyboard::Numpad8:
							keyPressed = '8';
							break;

						case sf::Keyboard::Num9:
						case sf::Keyboard::Numpad9:
							keyPressed = '9';
							break;
						}

						if (keyPressed != 'Q')
						{
							ipDigitsEntered += keyPressed;
							toConnectText.setString("IP TO CONNECT TO:\n   " + strigToIP(ipDigitsEntered));
						}
					}
				}			
			}		
		}
	}

	void ConnectState::Update(float dt)
	{

	}

	void ConnectState::Draw(float dt)
	{
		_data->window.clear();

		if (!isCreatingGame && !isJoiningGame)
		{
			_data->window.draw(createGameText);
			_data->window.draw(joinGameText);
			_data->window.draw(localIPText);
		}
		else if (isCreatingGame)
		{
			_data->window.draw(waitingForConnectionText);
		}
		else if (isJoiningGame)
		{
			_data->window.draw(toConnectText);
		}
		
		_data->window.display();
	}

	std::string ConnectState::strigToIP(std::string str)
	{
		std::string templ = "___.___._._";

		for (int i = 0, j = 0; i < str.size(); i++, j++)
		{
			if (j == 3 || j == 7 || j == 9 || j == 11)
			{
				j++;
			}
			templ[j] = str[i];
		}

		return templ;
	}
}