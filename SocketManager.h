#pragma once

#include <SFML/Network.hpp>

class SocketManager
{
public:
	enum PacketType {
		Unknown,
		Connection,
		PlayerPos,
		Projectile,
	};
	static void init(std::string playerName, sf::IpAddress addr, unsigned int port);
	static void send(sf::Packet packet);
	static bool isOnline() { return _onlineMode; };

private:
	static void handlePackets();
	static sf::Thread _packetsThread;

	static void handlePlayerConnection(sf::Packet packet);
	static void handlePlayerPos(sf::Packet packet);
	static void handleProjectile(sf::Packet packet);

	static std::string _name;
	static bool _onlineMode;
	static unsigned int _serverPort;
	static sf::UdpSocket _socket;
	static sf::IpAddress _serverIP;
};

template <typename T>
inline sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2<T>& vec)
{
	packet << vec.x;
	packet << vec.y;
	return packet;
}

sf::Packet& operator >>(sf::Packet& packet, SocketManager::PacketType& pt);
sf::Packet& operator <<(sf::Packet& packet, const SocketManager::PacketType& pt);
template <typename T>
sf::Packet& operator >>(sf::Packet& packet, sf::Vector2<T>& vec);

template<typename T>
inline sf::Packet & operator>>(sf::Packet & packet, sf::Vector2<T>& vec)
{
	packet >> vec.x;
	packet >> vec.y;
	return packet;
}
