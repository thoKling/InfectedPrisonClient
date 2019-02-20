#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	// M�thode qui permet de cr�er la musique principale du jeu
	void createMainTheme();

	// M�thode qui permet de jouer la musique principale du jeu
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

	// identifiant suivant servant � la cr�ation d'un nouveau son
	unsigned int _nextId;

};

