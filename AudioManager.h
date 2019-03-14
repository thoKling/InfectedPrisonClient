#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class AudioManager
{
public:
	AudioManager() = delete;

	// Méthode qui permet de créer la musique principale du jeu
	static void createMainTheme();

	// Méthode qui permet de jouer la musique principale du jeu
	static void playMainTheme();
	static void stopMainTheme();

	static bool isMainThemePlayed();

	// Charge et joue un son dont le nom de fichier (sans l'extension ni le dossier parent) est donné en paramètre
	static void playSound(std::string nameSound);


	static bool _isMainThemePlayed;

private:
	// Musique principale du jeu
	static sf::Music _mainTheme;

	
	static sf::Sound sound;
	
	// Liste des buffers
	static std::map<std::string, sf::SoundBuffer*> _sounds;
};

