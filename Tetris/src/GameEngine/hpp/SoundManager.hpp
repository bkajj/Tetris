#pragma once

#include <SFML/Audio.hpp>
#include <map>

namespace hgw
{
	struct SoundData
	{
		SoundData(std::string soundFilePath);

		sf::Sound sound;
		sf::SoundBuffer buffer;

		static float globalSoundVolume;
		static bool globalMute;

		bool isLoaded = false;
	};

	class SoundManager
	{
	public:
		SoundManager() {};
		~SoundManager() {};

		void Play(SoundData sd);
		void Play(SoundData sd, float tempVolumeToPlay);

		//init sd here
		//SoundData StartGame(FILENAME)...
	};
}