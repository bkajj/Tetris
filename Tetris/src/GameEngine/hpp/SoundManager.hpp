#pragma once

#include <SFML/Audio.hpp>
#include <map>

namespace hgw
{
	class SoundManager
	{
	public:
		SoundManager() {};
		~SoundManager() {};

		void LoadSoundBuffer(std::string name, std::string filename);
		sf::SoundBuffer &GetSoundBuffer(std::string name);

	private:
		std::map<std::string, sf::SoundBuffer> _soundBuffers;
	};
}