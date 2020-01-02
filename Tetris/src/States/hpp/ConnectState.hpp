#pragma once
#include "src/GameEngine/hpp/State.hpp"
#include "src/GameEngine/hpp/Game.hpp"
#include <SFML/Network.hpp>
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

	private:
		GameDataRef _data;

		bool isJoiningGame = false, isCreatingGame = false;
		std::string ipDigitsEntered = "";
		sf::TcpSocket socket, client;
		sf::TcpListener server;
		sf::IpAddress ipToConnectTo;

		sf::Text createGameText, joinGameText;
		sf::Text localIPText;

		sf::Text toConnectText, waitingForConnectionText;
	};
}