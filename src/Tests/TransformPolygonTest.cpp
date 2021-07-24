#include "TransformPolygonMock.h"
#include <gtest/gtest.h>

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