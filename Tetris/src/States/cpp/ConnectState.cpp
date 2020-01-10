#include "src/States/hpp/ConnectState.hpp"
#include "src/States/hpp/GameState.hpp"
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

		ipConnectText.setString("IP TO CONNECT TO:\n   _.___.___.__");
		ipConnectText.setFont(font);
		ipConnectText.setCharacterSize(50);

		portConnectText.setString("PORT TO CONNECT TO:\n	   _____");
		portConnectText.setFont(font);
		portConnectText.setCharacterSize(50);

		waitingForConnectionText.setString("WAITING FOR CONNECTION");
		waitingForConnectionText.setFont(font);
		waitingForConnectionText.setCharacterSize(50);

		createGameText.setPosition((APP_WIDTH - createGameText.getGlobalBounds().width) / 2, 300);
		joinGameText.setPosition((APP_WIDTH - joinGameText.getGlobalBounds().width) / 2, createGameText.getPosition().y + 100);
		localIPText.setPosition((APP_WIDTH - localIPText.getGlobalBounds().width) / 2, 150);
		localPortText.setPosition((APP_WIDTH - localPortText.getGlobalBounds().width) / 2, localIPText.getPosition().y + 70);

		ipConnectText.setPosition((APP_WIDTH - ipConnectText.getGlobalBounds().width) / 2, 200);
		portConnectText.setPosition((APP_WIDTH - portConnectText.getGlobalBounds().width) / 2, ipConnectText.getPosition().y + 150);
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
			if (!isCreatingGame && !isJoiningGame)
			{
				if (_data->input.IsTextClicked(createGameText, sf::Mouse::Left, event.type, _data->window)) //create game text
				{
					isCreatingGame = true;

					_data->network.addClient("enemy");
					//start listening from other thread, cause sf::TcpListener::listen() blocks thread from which is called
					gameCreated = std::async( &NetworkManager::listenForConnection, &_data->network, sf::Socket::AnyPort, std::ref(_data->network.getTcpClient("enemy")));
					std::this_thread::sleep_for(std::chrono::milliseconds(1)); //listenForConnetction must be called first in order to get localport

					localport = _data->network._tcpServer.getLocalPort();
					localPortText.setString("Your Port: " + std::to_string(localport));

					waitingClock.restart();
				}
				else if (_data->input.IsTextClicked(joinGameText, sf::Mouse::Left, event.type, _data->window)) //join game text
				{
					isJoiningGame = true;
				}
			}
			else if (isJoiningGame) //join game clicked
			{
				if (_data->input.IsTextClicked(ipConnectText, sf::Mouse::Left, event.type, _data->window, sf::Vector2i(1, 2))) //ip to connect to text
				{
					isTypingIp = true;
					isTypingPort = false;
				}
				else if (_data->input.IsTextClicked(portConnectText, sf::Mouse::Left, event.type, _data->window, sf::Vector2i(1, 2))) //port to connect to text
				{
					isTypingIp = false;
					isTypingPort = true;
				}
				if (event.type == sf::Event::KeyPressed)
				{
					char digitPressed = getPressedDigit(event);

					if (isTypingIp)
					{
						if ((event.key.code == sf::Keyboard::BackSpace || event.key.code == sf::Keyboard::Backspace) && ipDigitsEntered.size() > 0) //removing ip digit
						{
							isIpFullyEnterd = false;
							ipDigitsEntered.erase(ipDigitsEntered.end() - 1);
							ipConnectText.setString("IP TO CONNECT TO:\n   " + strigToIP(ipDigitsEntered));
						}
						else if (ipDigitsEntered.size() < 9 && digitPressed != 'X') //adding ip digit
						{
							isIpFullyEnterd = false;
							ipDigitsEntered += digitPressed;
							ipConnectText.setString("IP TO CONNECT TO:\n   " + strigToIP(ipDigitsEntered));
						}
						else if (ipDigitsEntered.size() == 9)
						{
							isIpFullyEnterd = true;
						}
					}

					if (isTypingPort)
					{
						if ((event.key.code == sf::Keyboard::BackSpace || event.key.code == sf::Keyboard::Backspace) && portDigitsEntered.size() > 0) //removing ip digit
						{
							isPortFullyEnterd = false;
							portDigitsEntered.erase(portDigitsEntered.end() - 1);
							portConnectText.setString("PORT TO CONNECT TO:\n       " + stringToPort(portDigitsEntered));
						}
						else if (portDigitsEntered.size() < 5 && digitPressed != 'X') //adding ip digit
						{
							isPortFullyEnterd = false;
							portDigitsEntered += digitPressed;
							portConnectText.setString("PORT TO CONNECT TO:\n       " + stringToPort(portDigitsEntered));
						}
						else if (portDigitsEntered.size() == 5)
						{
							isPortFullyEnterd = true;
						}
					}

					if ((event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return) && isIpFullyEnterd && isPortFullyEnterd) //joining game
					{
						/*ipToConnectTo = sf::IpAddress(strigToIP(ipDigitsEntered));
						portToConnectTo = std::stoi(portDigitsEntered);
						_data->network.addTcpSocket("socket", ipToConnectTo, portToConnectTo);
						*/
						portToConnectTo = std::stoi(portDigitsEntered);
						ipToConnectTo = sf::IpAddress("127.0.0.1"); //temp connection with localhost

						if (_data->network.addTcpSocket("enemy", "127.0.0.1", portToConnectTo))
						{
							_data->machine.AddState(StateRef(new GameState(_data, true)));
						}
					}
				}
			}
		}
	}

	void ConnectState::Update(float dt)
	{
		if (isCreatingGame)
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
		}

		if (gameCreated.valid() && gameCreated.wait_for(std::chrono::microseconds(1)) == std::future_status::ready && gameCreated.get())
		{
			_data->machine.AddState(StateRef(new GameState(_data, true)));
		}
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
			_data->window.draw(portConnectText);
			_data->window.draw(ipConnectText);
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