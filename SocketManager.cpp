#include "SocketManager.h"
#include "World.h"
#include <iostream>

#include "ProjectilesManager.h"
#include "PlayersManager.h"

bool SocketManager::_onlineMode = false;
unsigned int SocketManager::_serverPort;
unsigned int SocketManager::_playerConnected = 0;
unsigned int SocketManager::_playerId = 0;
sf::UdpSocket SocketManager::_socket;
sf::IpAddress SocketManager::_serverIP;
sf::Thread SocketManager::_packetsThread(&handlePackets);
std::vector<SocketManager::player> SocketManager::_playersConnected;
std::string SocketManager::_name = "";

sf::Packet& operator >>(sf::Packet& packet, std::vector<std::vector<int>>& myVec)
{
	for (size_t i = 0; i < myVec.size(); i++)
	{
		for (size_t j = 0; j < myVec[0].size(); j++)
		{
			packet >> myVec[i][j];
		}
	}
	return packet;
}


void SocketManager::init(sf::IpAddress addr, unsigned int port)
{
	_serverPort = port;
	_serverIP = addr;
	// on bind la socket
	if (_socket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
	{
		throw std::string("Impossible de lié la socket au port 10000");
	}
	sf::Packet packet;
	std::cin >> _name;
	packet << PacketType::Connection;
	send(packet);
	_onlineMode = true;
	///
	/// Réponse du serveur avec les informations
	///
	std::vector<std::vector<int>> level;
	unsigned short portS;
	sf::Packet response;
	if (_socket.receive(response, addr, portS) != sf::Socket::Done)
	{
		throw std::string("Erreur lors de la récéption du paquet");
	}
	// on définit le niveau à l'aide de numéro de tuiles
	level.resize(16);
	for (size_t i = 0; i < level.size(); i++)
	{
		level[i].resize(32);
	}
	response >> _playerId >> _playerConnected >> level;
	World::getInstance()->loadMap(level, sf::Vector2i(0, 0));
	// exécute le thread
	_packetsThread.launch();
}

void SocketManager::send(sf::Packet packet)
{
	packet <<_name;
	_socket.send(packet, _serverIP, _serverPort);
}

void SocketManager::handlePackets()
{
///
/// Boucle principale
///
	sf::Packet packet;
	sf::IpAddress sender;
	unsigned short port;
	while (_socket.receive(packet, sender, port) == sf::Socket::Done) {
		PacketType packetType = PacketType::Unknown;
		packet >> packetType;
		switch (packetType) {
		case PacketType::Connection:
			handlePlayerConnection(packet);
			break;
		case PacketType::PlayerPos:
			handlePlayerPos(packet);
			break;
		case PacketType::Projectile:
			handleProjectile(packet);
			break;
		default:
			std::cout << "Unknown packetType from " << sender << std::endl;
			break;
		}
	}
}

void SocketManager::handlePlayerConnection(sf::Packet packet)
{
	std::string name;
	packet >> name;
	std::cout << name << " vient de se connecter !" << std::endl;
	unsigned int id = PlayersManager::createPlayer({128,200});
	_playersConnected.push_back({id, name});
}

void SocketManager::handlePlayerPos(sf::Packet packet)
{
	std::string name;
	packet >> name;
	sf::Vector2f pos;
	packet >> pos;
	float rotation;
	packet >> rotation;
	unsigned int id = 0;
	for (auto player = _playersConnected.begin(); player != _playersConnected.end(); player++)
	{
		if (player->name == name)
			id = player->localCharId;
	}
	if (id) {
		//PlayersManager::getPlayers()[id]->setPosition(pos);
		//PlayersManager::getPlayers()[id]->setRotation(rotation);
	}
}

void SocketManager::handleProjectile(sf::Packet packet)
{
	std::string name;
	packet >> name;
	sf::Vector2f pos;
	packet >> pos;
	float rotation;
	packet >> rotation;
	int weaponType;
	packet >> weaponType;
	ProjectilesManager::createProjectile(pos, rotation, WeaponType(weaponType), false);
}

sf::Packet & operator>>(sf::Packet & packet, SocketManager::PacketType & pt)
{
	int temp;
	packet >> temp;
	pt = SocketManager::PacketType(temp);
	return packet;
}

sf::Packet & operator<<(sf::Packet & packet, const SocketManager::PacketType & pt)
{
	packet << (int)pt;
	return packet;
}
