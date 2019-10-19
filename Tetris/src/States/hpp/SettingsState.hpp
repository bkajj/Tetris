#pragma once
#include "src/GameEngine/hpp/State.hpp"
#include "src/GameEngine/hpp/Game.hpp"

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
		void setTextString(GameData::variableNames variableName);
		
		GameDataRef _data;
	};
}