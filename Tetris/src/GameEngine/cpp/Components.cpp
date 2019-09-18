#include "src/GameEngine/hpp/Components.hpp"
#include <iostream>

//definitions here, not in DEFINE.hpp
#define VOLUME_BAR_FILEPATH ""
#define VOLUME_POINT_FILEPATH ""

namespace hgw
{
	namespace cmp
	{
		VolumeBar::VolumeBar(GameDataRef data) : _data(data)
		{
			Init();
		}

		void VolumeBar::Init()
		{
			this->_data->graphics.LoadTexture("Bar", VOLUME_BAR_FILEPATH);
			this->_data->graphics.LoadTexture("Point", VOLUME_POINT_FILEPATH);

			this->_bar.setTexture(this->_data->graphics.GetTexture("Bar"));
			this->_point.setTexture(this->_data->graphics.GetTexture("Point"));

			this->_point.setOrigin(this->_point.getGlobalBounds().width / 2, this->_point.getGlobalBounds().height / 2);
		}

		void VolumeBar::Attach(sf::Sprite sprite, sf::Vector2f posDifference, float volume)
		{
			this->_bar.setPosition(sprite.getPosition().x - (_bar.getGlobalBounds().width - sprite.getGlobalBounds().width) / 2, 
				sprite.getPosition().y - posDifference.y);
			this->_point.setPosition(volume / 100 * this->_bar.getGlobalBounds().width + this->_bar.getPosition().x,
				sprite.getPosition().y - posDifference.y + this->_point.getGlobalBounds().height / 2);
		}

		void VolumeBar::MovePoint()
		{
			sf::Mouse mouse;
			sf::IntRect tempRect(_bar.getPosition().x, _bar.getPosition().y, _bar.getLocalBounds().width, _bar.getLocalBounds().height);

			if (tempRect.contains(mouse.getPosition(this->_data->window)))
			{
				this->_point.setPosition(mouse.getPosition(this->_data->window).x, _point.getPosition().y);
			}
		}

		float VolumeBar::GetVolume()
		{
			float barSize = this->_bar.getGlobalBounds().width;
			float barpoint = this->_bar.getPosition().x;
			float pointPos = sf::Mouse::getPosition(this->_data->window).x - barpoint;

			if (std::round(pointPos) / barSize * 100 > 0)
			{
				return std::round(pointPos) / barSize * 100;
			}
			else
			{
				return 0;
			}
		}

	}
}