	#include "src/GameEngine/hpp/MusicManager.hpp"
#include <iostream>

namespace hgw
{
	void MusicManager::Play(sf::Music &music, std::string filepath, bool loop = true)
	{
		if (music.openFromFile(filepath))
		{
			music.setVolume(globalVolume);
			music.setLoop(loop);
			music.play();
		}
	}

	void MusicManager::Stop(sf::Music &music)
	{
		music.stop();
	}
}