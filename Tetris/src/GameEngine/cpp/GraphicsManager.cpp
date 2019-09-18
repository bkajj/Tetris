#include "src/GameEngine/hpp/GraphicsManager.hpp"

namespace hgw
{
	void GraphicsManager::LoadTexture(std::string name, std::string filename)
	{
		sf::Texture tex;

		if (tex.loadFromFile(filename))
		{
			this->_textures[name] = tex;
		}
	}
	sf::Texture &GraphicsManager::GetTexture(std::string name)
	{
		return this->_textures.at(name);
	}

	void GraphicsManager::LoadFont(std::string name, std::string filename)
	{
		sf::Font font;

		if (font.loadFromFile(filename))
		{
			this->_fonts[name] = font;
		}
	}
	sf::Font &GraphicsManager::GetFont(std::string name)
	{
		return this->_fonts.at(name);
	}

	void GraphicsManager::FadeIn(int changeValue, int endValue, sf::Sprite sprite)
	{
		if (static_cast<int>(sprite.getColor().a) <= (endValue - changeValue))
		{
			sprite.setColor(sf::Color(
				static_cast<int>(sprite.getColor().r), 
				static_cast<int>(sprite.getColor().g),
				static_cast<int>(sprite.getColor().b),
				static_cast<int>(sprite.getColor().a) + changeValue));
		}
	}
}