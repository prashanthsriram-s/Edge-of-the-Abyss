#ifndef TRANSFORMPOLYGONMOCK
#define TRANSFORMPOLYGONMOCK

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <cassert>
#include "../Util/Constants.h"

std::vector<sf::Vector2f> transformPolygonMock(std::vector<sf::Vector2f> untransformed_cords
	, sf::Vector2f m_scale, float m_rotation)
{
	std::vector<sf::Vector2f> transformed_cords;
	sf::Vector2f tilecenter{CONSTANTS::TILE_WIDTH/2.f, CONSTANTS::TILE_HEIGHT/2.f};

	for(auto pt: untransformed_cords){
		pt = pt - tilecenter;

		assert(fabs(m_scale.x)==1 && fabs(m_scale.y)==1);
		pt = sf::Vector2f(pt.x*m_scale.x, pt.y*m_scale.y);

		assert(static_cast<int>(m_rotation)%90 <= 2);
		double theta = m_rotation * 3.14159265 / 180;
		pt = sf::Vector2f(pt.x*cos(theta) - pt.y*sin(theta)
			, pt.x*sin(theta) + pt.y*cos(theta));

		pt += tilecenter;

		transformed_cords.push_back(pt);
	}
	return transformed_cords;
}

#endif