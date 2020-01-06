#pragma once
#include "src/GameEngine/hpp/State.hpp"
#include "src/GameEngine/hpp/Game.hpp"
#include <SFML/Network.hpp>
#include <thread>

namespace hgw
{
	class ConnectState : public State
	{
	public:
		ConnectState(GameDataRef _data);

		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

		std::string strigToIP(std::string str);
		std::string stringToPort(std::string str);
		char getPressedDigit(sf::Event event);

	private:
		GameDataRef _data;

		sf::Text createGameText, joinGameText; //join or create choice
		bool isJoiningGame = false, isCreatingGame = false;

		sf::Text localIPText, localPortText; //create game
		std::thread createGameThread;
		sf::Text waitingForConnectionText;
		sf::Clock waitingClock;
		std::string waitingDots = "";
		bool dotsGoingForward = true;
		unsigned short localport = 0;
		sf::TcpSocket client;

		sf::Text ipConnect, portConnect; //join game
		sf::IpAddress ipToConnectTo;
		bool isTypingIp = false, isTypingPort = false;
		std::string ipDigitsEntered = "", portDigitsEntered = "";
		sf::TcpSocket socket;
	};
}