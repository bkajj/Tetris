#pragma once
#include "src/GameEngine/hpp/State.hpp"
#include "src/GameEngine/hpp/Game.hpp"
#include "src/GameEngine/hpp/Components.hpp"

namespace hgw
{
	class SettingsState : public State
	{
	public:
		SettingsState(GameDataRef _data);
		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		sf::Text returnText, originalColorText, drawFullGridText;
		float soundVolume = 100.0, musicVolume = 100.0;
		sf::Sprite soundOff, soundOn;
		sf::Sprite musicOff, musicOn;
		cmp::VolumeBar soundBar, musicBar;
		
		void setTextString(GameData::variableNames variableName);
		
		GameDataRef _data;
	};
}