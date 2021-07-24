#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <gtest/gtest.h>
#include "../Util/Constants.h"

std::vector<sf::Vector2f> transformPolygonMock(std::vector<sf::Vector2f> untransformed_cords, sf::Vector2f m_scale, float m_rotation){
	std::vector<sf::Vector2f> transformed_cords;
	sf::Vector2f tilecenter{CONSTANTS::TILE_WIDTH/2.f, CONSTANTS::TILE_HEIGHT/2.f};

	for(auto pt: untransformed_cords){
		pt = pt - tilecenter;// relative position abt center

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

class TRANSFORM_POLYGON: public ::testing::Test {
protected:
	std::vector<sf::Vector2f> untransformed_test_corners;

	void SetUp() override{
		untransformed_test_corners = {{0, 10}, {42, 10}, {0, 42}, {42, 42}};
	}
};

TEST_F(TRANSFORM_POLYGON, NoTransform){
	std::vector<sf::Vector2f> expected_result{{0, 10}, {42, 10}, {0, 42}, {42, 42}};
	std::vector<sf::Vector2f> result = transformPolygonMock(untransformed_test_corners, {1,1}, 0.f);

	ASSERT_EQ(expected_result, result);
}

TEST_F(TRANSFORM_POLYGON, VerticalFlip){
	std::vector<sf::Vector2f> expected_result{{0, 32}, {42, 32}, {0, 0}, {42, 0}};
	std::vector<sf::Vector2f> result = transformPolygonMock(untransformed_test_corners, {1,-1}, 0.f);

	ASSERT_EQ(expected_result, result);
}

TEST_F(TRANSFORM_POLYGON, HorizontalFlip){
	std::vector<sf::Vector2f> expected_result{{42, 10}, {0, 10}, {42, 42}, {0, 42}};
	std::vector<sf::Vector2f> result = transformPolygonMock(untransformed_test_corners, {-1,1}, 0.f);

	ASSERT_EQ(expected_result, result);
}

TEST_F(TRANSFORM_POLYGON, Clockwise_rotation_by_90_degrees){
	std::vector<sf::Vector2f> expected_result{{32, 0}, {32, 42}, {0, 0}, {0, 42}};
	std::vector<sf::Vector2f> result = transformPolygonMock(untransformed_test_corners, {1,1}, 90.f);

	ASSERT_EQ(expected_result, result);
}

TEST_F(TRANSFORM_POLYGON, Anticlockwise_rotation_by_90_degrees){
	std::vector<sf::Vector2f> expected_result{{10, 42}, {10, 0}, {42, 42}, {42, 0}};
	std::vector<sf::Vector2f> result = transformPolygonMock(untransformed_test_corners, {1,1}, -90.f);

	ASSERT_EQ(expected_result, result);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}