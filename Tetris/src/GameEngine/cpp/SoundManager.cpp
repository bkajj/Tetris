#include "src/GameEngine/hpp/SoundManager.hpp"
#include <iostream>

namespace hgw
{

	void SoundManager::Play(SoundData sd)
	{
		if (sd.isLoaded && !SoundData::globalMute)
		{
			sd.sound.setVolume(SoundData::globalSoundVolume);
			sd.sound.play();
		}
	}

	void SoundManager::Play(SoundData sd, float tempVolume)
	{
		if (sd.isLoaded && !SoundData::globalMute)
		{
			sd.sound.setVolume(tempVolume);
			sd.sound.play();
		}
	}

	SoundData::SoundData(std::string soundFilePath)
	{
		//remember: limit of 256 sounds

		try
		{
			buffer.loadFromFile(soundFilePath);
			sound.setBuffer(buffer);

			isLoaded = true;
			sound.setVolume(globalSoundVolume);
		}
		catch (const std::exception& e)
		{
			std::cout << "exception: " << e.what() << std::endl;
		}
	}

	float SoundData::globalSoundVolume = 100.0f;
	bool SoundData::globalMute = false;
}