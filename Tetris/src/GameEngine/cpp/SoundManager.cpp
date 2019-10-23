#include "src/GameEngine/hpp/SoundManager.hpp"
#include <iostream>

namespace hgw
{
	void SoundManager::LoadSoundBuffer(std::string name, std::string filename)
	{
		sf::SoundBuffer sb;

		if (sb.loadFromFile(filename) && _soundBuffers.find(name) == _soundBuffers.end()) //if loaded properly and value doesn't exist in map
		{
			_soundBuffers[name] = sb;
		}
	}
	sf::SoundBuffer &SoundManager::GetSoundBuffer(std::string name)
	{
		return _soundBuffers.at(name);
	}
}