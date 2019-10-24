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

		void Play(sf::Sound &sound);

		float globalVolume = 100.0f;
	private:
		std::map<std::string, sf::SoundBuffer> _soundBuffers;	
	};
}