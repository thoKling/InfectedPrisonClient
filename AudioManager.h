#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	// Méthode qui permet de créer la musique principale du jeu
	void createMainTheme();

	// Méthode qui permet de jouer la musique principale du jeu
	void playMainTheme();

	void createSoundBuffer();

	sf::Sound gun();

	sf::SoundBuffer _buffer;
	sf::Sound _sound;

private:
	// Musique principale du jeu
	sf::Music _mainTheme;
	
	// Liste des buffers
	std::map<unsigned int, sf::SoundBuffer> _buffers;

	// Liste des sons
	std::map<unsigned int, sf::Sound*> _sounds;

	// identifiant suivant servant à la création d'un nouveau son
	unsigned int _nextId;

};

