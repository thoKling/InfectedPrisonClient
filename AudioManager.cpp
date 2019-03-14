#include "AudioManager.h"
#include <iostream>

bool AudioManager::_isMainThemePlayed = false;
sf::Music AudioManager::_mainTheme;
std::map<std::string, sf::SoundBuffer*> AudioManager::_sounds;
sf::Sound AudioManager::sound;

void AudioManager::createMainTheme()
{
	if (!_mainTheme.openFromFile("Ressources/Sounds/infectedMusic.wav"))
		throw std::string("Impossible de charger la musique");
	_mainTheme.setLoop(true);
}

void AudioManager::playMainTheme()
{
	_mainTheme.play();
	_isMainThemePlayed = true;
}

void AudioManager::stopMainTheme() {
	_mainTheme.pause();
	_isMainThemePlayed = false;
}

bool AudioManager::isMainThemePlayed() {
	return _isMainThemePlayed;
}

void AudioManager::playSound(std::string nameSound)
{
	// Si la map contient ce son
	std::map<std::string, sf::SoundBuffer*>::iterator it = _sounds.find(nameSound);
	if (it != _sounds.end()) {
		sound.setBuffer(*(it->second));
	}
	else {
		sf::SoundBuffer* buffer = new sf::SoundBuffer();
		if (!buffer->loadFromFile("Ressources/Sounds/" + nameSound + ".wav"))
			throw std::string("Impossible de charger le son " + nameSound + ".wav");
		_sounds.insert({ nameSound, buffer });
	sound.setBuffer(*buffer);
	}
	sound.play();
}
