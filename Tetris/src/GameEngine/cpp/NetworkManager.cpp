#include "src/GameEngine/hpp/NetworkManager.hpp"
#include <string>
namespace hgw
{
	void NetworkManager::addClient(std::string key)
	{
		//_tcpClients.emplace(key, sf::TcpSocket{});
	}

	sf::TcpSocket& NetworkManager::getTcpClient(std::string name)
	{
		return *_tcpClients[name];
	}

	sf::TcpSocket& NetworkManager::getTcpSocket(std::string name)
	{
		return *_tcpSockets[name];
	}

	sf::UdpSocket& NetworkManager::getUdpSocket(std::string name)
	{
		return *_udpSockets[name];
	}	

	void NetworkManager::addTcpSocket(std::string key, sf::IpAddress ip, unsigned short port, sf::Time timeout)
	{
		_tcpSockets[key] = std::make_unique<sf::TcpSocket>();
		if (_tcpSockets[key]->connect(ip, port, timeout) != sf::Socket::Done)
		{
			std::cout << "[tcp socket] connection error" << std::endl;
		}
		else
		{
			std::cout << "[tcp socket] connected successfully" << std::endl;
		}
	}

	void NetworkManager::addUdpSocket(std::string key, unsigned short port)
	{
		_udpSockets[key] = std::make_unique<sf::UdpSocket>();
		if (_udpSockets[key]->bind(port) != sf::Socket::Done)
		{
			std::cout << "[udp socket] binding error" << std::endl;
		}
		else
		{
			std::cout << "[tcp socket] binded successfully" << std::endl;
		}
	}

	void NetworkManager::sendPacket(sf::Packet &packet, sf::TcpSocket &tcpSocket)
	{
		tcpSocket.send(packet);
	}

	void NetworkManager::sendPacket(sf::Packet &packet, sf::UdpSocket &udpSocket, sf::IpAddress ip, unsigned short port)
	{
		udpSocket.send(packet, ip, port);
	}

	void NetworkManager::recievePacket(sf::Packet &packet, sf::TcpSocket &tcpSocket)
	{
		tcpSocket.receive(packet);
	}

	void NetworkManager::recievePacket(sf::Packet &packet, sf::UdpSocket &udpSocket, sf::IpAddress ip, unsigned short port)
	{
		udpSocket.receive(packet, ip, port);
	}

	void NetworkManager::listen(unsigned short port, sf::TcpSocket &client)
	{
		if (_tcpServer.listen(port) != sf::Socket::Done)
		{
			std::cout << "[server] Error Ocurred while listening to " << port << std::endl;
		}

		if (_tcpServer.accept(client) != sf::Socket::Done)
		{
			std::cout << "[server] Error Ocurred while connecting to client" << std::endl;
		}
		else
		{
			std::cout << "[server] Connection accepted successfully" << std::endl;
		}	
	}
}