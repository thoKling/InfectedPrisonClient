#pragma once

#include <SFML/Graphics.hpp>

constexpr auto PI = 3.14159265;

#define toRadians PI / 180.0
#define toDegrees 180.0 / PI

class Utils
{
public:
	// Récupération du numéro de quadrant dans lequel se situe la pos2 par rapport a la pos1
	static int getQuadrant(const sf::Vector2f& pos1, const sf::Vector2f& pos2);
	// Renvoit le vecteur unitaire de la startPos à la endPos
	static sf::Vector2f getVecUnit(const sf::Vector2f& startPos, const sf::Vector2f& endPos);
	// Renvoit la distance entre 2 coordonnées
	static double distance(const sf::Vector2f& pos1, const sf::Vector2f& pos2);
	// Fonction split pour les strings, renvoit les différents morceaux de la chaine entre les delimiter
	static std::vector<std::string> split(std::string stringToSplit, std::string delimiter);
};

