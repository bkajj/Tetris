#include "src/States/hpp/ConnectState.hpp"
#include "src/DEFINE.hpp"
#include <iostream>
#include <SFML/Network.hpp>
#include <thread>

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

		localPortText.setString("Your Port: _____");
		localPortText.setFont(font);
		localPortText.setCharacterSize(50);

		ipConnect.setString("IP TO CONNECT TO:\n   _.___.___.__");
		ipConnect.setFont(font);
		ipConnect.setCharacterSize(50);

		portConnect.setString("PORT TO CONNECT TO:\n	   _____");
		portConnect.setFont(font);
		portConnect.setCharacterSize(50);

		waitingForConnectionText.setString("WAITING FOR CONNECTION");
		waitingForConnectionText.setFont(font);
		waitingForConnectionText.setCharacterSize(50);

		createGameText.setPosition((APP_WIDTH - createGameText.getGlobalBounds().width) / 2, 300);
		joinGameText.setPosition((APP_WIDTH - joinGameText.getGlobalBounds().width) / 2, createGameText.getPosition().y + 100);
		localIPText.setPosition((APP_WIDTH - localIPText.getGlobalBounds().width) / 2, 150);
		localPortText.setPosition((APP_WIDTH - localPortText.getGlobalBounds().width) / 2, localIPText.getPosition().y + 70);

		ipConnect.setPosition((APP_WIDTH - ipConnect.getGlobalBounds().width) / 2, 200);
		portConnect.setPosition((APP_WIDTH - portConnect.getGlobalBounds().width) / 2, ipConnect.getPosition().y + 150);
		waitingForConnectionText.setPosition((APP_WIDTH - waitingForConnectionText.getGlobalBounds().width) / 2, localPortText.getPosition().y + 70);
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
			else if (_data->input.IsTextClicked(createGameText, sf::Mouse::Left, event.type, _data->window)) //create game text
			{
				isCreatingGame = true;
				_data->network.addClient("enemy");
				createGameThread = std::thread{ &NetworkManager::listenForConnection, &_data->network, sf::Socket::AnyPort, std::ref(_data->network.getTcpClient("enemy")) };
				std::this_thread::sleep_for(std::chrono::milliseconds(1)); //listenForConnetction must be called first in order to get localport
				localport = _data->network._tcpServer.getLocalPort();
				localPortText.setString("Your Port: " + std::to_string(localport));

				waitingClock.restart();
			}
			else if (_data->input.IsTextClicked(joinGameText, sf::Mouse::Left, event.type, _data->window)) //join game text
			{
				isJoiningGame = true;		
			}
			else if (_data->input.IsTextClicked(ipConnect, sf::Mouse::Left, event.type, _data->window, sf::Vector2i(1, 2)) && isJoiningGame) //ip to connect to text
			{
				isTypingIp = true;
				isTypingPort = false;
			}
			else if (_data->input.IsTextClicked(portConnect, sf::Mouse::Left, event.type, _data->window, sf::Vector2i(1, 2)) && isJoiningGame) //port to connect to text
			{
				isTypingIp = false;
				isTypingPort = true;
			}
			else if (event.type == sf::Event::KeyPressed && isJoiningGame)
			{
				char digitPressed = getPressedDigit(event);
				
				if (isTypingIp)
				{
					if ((event.key.code == sf::Keyboard::BackSpace || event.key.code == sf::Keyboard::Backspace) && ipDigitsEntered.size() > 0) //removing ip digit
					{
						ipDigitsEntered.erase(ipDigitsEntered.end() - 1);
						ipConnect.setString("IP TO CONNECT TO:\n   " + strigToIP(ipDigitsEntered));
					}
					else if (ipDigitsEntered.size() < 9 && digitPressed != 'X') //adding ip digit
					{
						ipDigitsEntered += digitPressed;
						ipConnect.setString("IP TO CONNECT TO:\n   " + strigToIP(ipDigitsEntered));
					}
				}
				
				if(isTypingPort)
				{
					if ((event.key.code == sf::Keyboard::BackSpace || event.key.code == sf::Keyboard::Backspace) && portDigitsEntered.size() > 0) //removing ip digit
					{
						portDigitsEntered.erase(portDigitsEntered.end() - 1);
						portConnect.setString("PORT TO CONNECT TO:\n       " + stringToPort(portDigitsEntered));
					}
					else if (portDigitsEntered.size() < 5 && digitPressed != 'X') //adding ip digit
					{
						portDigitsEntered += digitPressed;
						portConnect.setString("PORT TO CONNECT TO:\n       " + stringToPort(portDigitsEntered));
					}
				}
				
				if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return) //joining game
				{
					ipToConnectTo = sf::IpAddress(strigToIP(ipDigitsEntered));
					_data->network.addTcpSocket("socket", ipToConnectTo, 53000);
					//ipToConnectTo = sf::IpAddress("127.0.0.1"); //temp connection with localhost
					//_data->network.addTcpSocket("socket", "127.0.0.1", 53000);
				}
				
			}		
		}
	}

	void ConnectState::Update(float dt)
	{
		if (waitingClock.getElapsedTime().asMilliseconds() >= 1000) //dots animation
		{
			if (dotsGoingForward) //adding dots
			{
				if (waitingDots.size() < 3)
				{
					waitingDots += ".";
				}
				else
				{
					dotsGoingForward = false;
				}
			}
			else //removing dots
			{
				if (waitingDots.size() > 0)
				{
					waitingDots.erase(waitingDots.end() - 1);
				}
				else
				{
					dotsGoingForward = true;
				}
			}

			waitingForConnectionText.setString("WAITING FOR CONNECTION" + waitingDots);

			waitingClock.restart();
		}

		std::cout << "PORT X: " << portConnect.getPosition().x << ",  Y: " << portConnect.getPosition().y << std::endl;
		std::cout << "PORT HEIGHt: " << portConnect.getGlobalBounds().height << std::endl;
		std::cout << "MOUSE X: " << sf::Mouse::getPosition(_data->window).x << ",  Y: " << sf::Mouse::getPosition(_data->window).y << std::endl;

		
	}

	void ConnectState::Draw(float dt)
	{
		_data->window.clear();

		if (!isCreatingGame && !isJoiningGame)
		{
			_data->window.draw(createGameText);
			_data->window.draw(joinGameText);
		}
		else if (isCreatingGame)
		{
			_data->window.draw(waitingForConnectionText);
			_data->window.draw(localIPText);
			_data->window.draw(localPortText);
		}
		else if (isJoiningGame)
		{
			_data->window.draw(portConnect);
			_data->window.draw(ipConnect);
		}
		
		_data->window.display();
	}

	std::string ConnectState::strigToIP(std::string str)
	{
		std::string templ = "_.___.___.__";

		for (int i = 0, j = 0; i < str.size(); i++, j++)
		{
			if (j == 1 || j == 5 || j == 9)
			{
				j++;
			}
			templ[j] = str[i];
		}

		return templ;
	}

	std::string ConnectState::stringToPort(std::string str)
	{
		std::string templ = "_____";

		for (int i = 0; i < str.size(); i++)
		{
			templ[i] = str[i];
		}

		return templ;
	}

	char ConnectState::getPressedDigit(sf::Event event) //if X returned - no key was pressed
	{
		char keyPressed = 'X';

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

		return keyPressed;
	}
}