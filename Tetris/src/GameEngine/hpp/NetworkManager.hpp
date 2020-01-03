#pragma once

#include <SFML/Network.hpp>
#include <iostream>
#include <map>

namespace hgw
{
	class NetworkManager
	{
	public:
		NetworkManager() {};
		~NetworkManager() {};

		void addClient(std::string key);
		sf::TcpSocket* getTcpClient(std::string name);

		sf::UdpSocket* getUdpSocket(std::string name);
		sf::TcpSocket* getTcpSocket(std::string name);	

		void addTcpSocket(std::string key, sf::IpAddress ip, unsigned short port, sf::Time timeout = sf::Time::Zero);
		void addUdpSocket(std::string key, unsigned short port);
		
		void sendPacket(sf::Packet &packet, sf::TcpSocket tcpSocket);
		void sendPacket(sf::Packet &packet, sf::UdpSocket udpSocket, sf::IpAddress ip, unsigned short port);

		void recievePacket(sf::Packet &packet, sf::TcpSocket tcpSocket);
		void recievePacket(sf::Packet &packet, sf::UdpSocket udpSocket, sf::IpAddress ip, unsigned short port);

		void listen(unsigned short port, sf::TcpSocket client);
	private:
		std::map<std::string, sf::TcpSocket*> _tcpSockets;
		std::map<std::string, sf::UdpSocket*> _udpSockets;

		sf::TcpListener _tcpServer;
		std::map<std::string, sf::TcpSocket*> _tcpClients;
	};
}