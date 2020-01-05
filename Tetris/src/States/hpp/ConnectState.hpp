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
		void waitForConnection();

	private:
		GameDataRef _data;

		bool isJoiningGame = false, isCreatingGame = false;
		std::string ipDigitsEntered = "";
		std::thread createGameThread;
		sf::Clock waitingClock;
		std::string waitingDots = "";
		bool dotsGoingForward = true;
		sf::TcpSocket socket, client;
		sf::TcpListener server;
		sf::IpAddress ipToConnectTo;

		sf::Text createGameText, joinGameText;
		sf::Text localIPText, localPortText;
		unsigned short localport = 0;


		sf::Text toConnectText, waitingForConnectionText;
	};
}