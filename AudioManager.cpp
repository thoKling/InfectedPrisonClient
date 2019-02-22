#include "AudioManager.h"


AudioManager::AudioManager() : _isMainThemePlayed(false), _nextId(0)
{
}


AudioManager::~AudioManager()
{
	for (auto it = _sounds.begin(); it != _sounds.end(); ++it)
	{
		delete it->second;
	}
}

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

void AudioManager::createSoundBuffer()
{
	if (!_buffer.loadFromFile("Ressources/Sounds/gun.wav"))
		throw std::string("Impossible de charger le son");
}

sf::Sound AudioManager::gun()
{
	//sf::Sound sound;
	_sound.setBuffer(_buffer);
	return _sound;
}
