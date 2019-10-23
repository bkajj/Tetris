#pragma once
#include <SFML/Audio.hpp>

namespace hgw
{
	class MusicManager
	{
	public:
		void Play(sf::Music &music, std::string filepath, float volume, bool loop);

		void Stop(sf::Music &music);
	};
}