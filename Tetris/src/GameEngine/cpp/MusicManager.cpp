#include "src/GameEngine/hpp/MusicManager.hpp"
#include <iostream>

//definitions here, not in DEFINE.hpp
#define GAME_MUSIC_FILEPATH ""


namespace hgw
{
	void MusicManager::LoopPlay(sf::Music &music, float soundVolume)
	{
		if (!muted)
		{
			if (music.getStatus() == music.Playing)
			{
				std::cout << "Music already playing" << std::endl;
			}
			else
			{
				if (!music.openFromFile(GAME_MUSIC_FILEPATH))
				{
					std::cout << "Error occured when opening music file" << std::endl;
				}
				else
				{
					if (music.getVolume() != musicVolume)
					{
						music.setVolume(musicVolume);
					}
					music.setLoop(true);
					music.play();
					loaded = true;
				}
			}
		}
		else
		{
			std::cout << "Music Muted" << std::endl;
		}
	}

	void MusicManager::Play(sf::Music &music, float soundVolume)
	{
		if (!muted)
		{
			if (music.getStatus() == music.Playing)
			{
				std::cout << "Music already playing" << std::endl;
			}
			else
			{
				if (!music.openFromFile(GAME_MUSIC_FILEPATH))
				{
					std::cout << "Error occured when opening music file" << std::endl;
				}
				else
				{
					if (music.getVolume() != musicVolume)
					{
						music.setVolume(musicVolume);
					}
					music.play();
					loaded = true;
				}
			}
		}
		else
		{
			std::cout << "Music Muted" << std::endl;
		}
	}

	void MusicManager::Mute()
	{
		if (muted)
		{
			std::cout << "Music already muted" << std::endl;
		}
		else
		{
			muted = true;
		}
	}

	void MusicManager::UnMute()
	{
		if (!muted)
		{
			std::cout << "Music already unmuted" << std::endl;
		}
		else
		{
			muted = false;
		}
	}

	bool MusicManager::IsMuted()
	{
		return muted;
	}

	bool MusicManager::IsLoaded()
	{
		return loaded;
	}

	void MusicManager::SetVolume(float volume)
	{
		musicVolume = volume;
		gameMusic.setVolume(volume);
	}

	float MusicManager::GetVolume()
	{
		return musicVolume;
	}
}