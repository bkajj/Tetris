#pragma once
#include <SFML/Audio.hpp>

namespace hgw
{
	class MusicManager
	{
	public:
		void Play(sf::Music &music, std::string filepath, bool loop);

		void Stop(sf::Music &music);

		float globalVolume = 100.0f;
	};
}