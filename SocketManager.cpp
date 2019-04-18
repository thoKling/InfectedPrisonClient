#include "SocketManager.h"
#include "World.h"
#include <iostream>

#include "ProjectilesManager.h"
#include "PlayersManager.h"
#include "ZombiesManager.h"
#include "Player.h"
#include "HUD.h"

bool SocketManager::_onlineMode = false;
unsigned int SocketManager::_serverPort;
sf::UdpSocket SocketManager::_socket;
sf::IpAddress SocketManager::_serverIP;
sf::Thread SocketManager::_packetsThread(&handlePackets);
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

void SocketManager::init(std::string playerName, sf::IpAddress addr, unsigned int port)
{
	_serverPort = port;
	_serverIP = addr;
	_name = playerName;
	// on bind la socket
	if (_socket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
	{
		throw std::string("Impossible de li� la socket au port 10000");
	}
	sf::Packet packet;
	packet << PacketType::Connection;
	send(packet);
	_onlineMode = true;
	///
	/// R�ponse du serveur avec les informations
	///
	unsigned short portS;
	sf::Packet response;
	if (_socket.receive(response, addr, portS) != sf::Socket::Done)
	{
		throw std::string("Erreur lors de la r�c�ption du paquet");
	}
	// on d�finit le niveau � l'aide de num�ro de tuiles
	std::vector<std::vector<int>> level;
	level.resize(16);
	for (size_t i = 0; i < level.size(); i++)
	{
		level[i].resize(32);
	}
	response >> level;
	World::getInstance()->loadMap(level, sf::Vector2i(0, 0));
	// ex�cute le thread
	_packetsThread.launch();
}

void SocketManager::stop()
{
	_packetsThread.terminate();
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
		case PacketType::CreateZombie:
			handleZombieCreation(packet);
			break;
		case PacketType::ZombieState:
			handleZombieState(packet);
			break;
		case PacketType::ZombieReceiveHit:
			handleZombieReceiveHit(packet);
			break;
		case PacketType::PlayerReceiveHit:
			handlePlayerReceiveHit(packet);
			break;
		case PacketType::NextWave:
			handleNextWave(packet);
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
	PlayersManager::createPlayer(name, {128,200});
}

void SocketManager::handlePlayerPos(sf::Packet packet)
{
	std::string name;
	packet >> name;
	sf::Vector2f pos;
	packet >> pos;
	float rotation;
	packet >> rotation;
	int showing;
	packet >> showing;

	PlayersManager::getPlayer(name)->setShowing(Player::Showing(showing));
	PlayersManager::getPlayer(name)->setPosition(pos);
	PlayersManager::getPlayer(name)->setRotation(rotation);
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

void SocketManager::handleZombieCreation(sf::Packet packet)
{
	std::cout << "ZombieCreation" << std::endl;
	sf::Vector2f pos;
	packet >> pos;
	std::cout << "position :" << pos.x << " " <<pos.y << std::endl;
	ZombiesManager::createZombie(pos);
}

void SocketManager::handleZombieState(sf::Packet packet)
{
	unsigned int id;
	sf::Vector2f pos;
	float rotation;
	packet >> id >> pos >> rotation;
	ZombiesManager::setState(id, pos, rotation);
}

void SocketManager::handleZombieReceiveHit(sf::Packet packet)
{
	unsigned int zombieId;
	packet >> zombieId;
	ZombiesManager::getZombies()[zombieId]->receiveHit(sf::Vector2f(0,0));
}

void SocketManager::handlePlayerReceiveHit(sf::Packet packet)
{
	std::string name;
	sf::Vector2f hitterPos;
	packet >> name >> hitterPos;
	PlayersManager::getPlayer(name)->receiveHit(hitterPos);
}

void SocketManager::handleNextWave(sf::Packet packet)
{
	int currentWave;
	packet >> currentWave;
	HUD::setWave(currentWave);
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
