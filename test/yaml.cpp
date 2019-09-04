#include "yaml.hpp"
#include "test/compare.hpp"

#include <gtest/gtest.h>


int main(int argc, char * * argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

namespace dr {

TEST(Yaml, vector) { //NOLINT
	ASSERT_EQ("{x: -0.100000, y: 1.200000, z: 2.300000}", toYaml(Eigen::Vector3d{-0.1, 1.2, 2.3})); //NOLINT
}

TEST(Yaml, quaternion) { //NOLINT
	ASSERT_EQ("{x: -0.100000, y: 1.200000, z: 2.300000, w: -1.900000}", toYaml(Eigen::Quaterniond{-1.9, -0.1, 1.2, 2.3})); //NOLINT
}

TEST(Yaml, pose) { //NOLINT
	std::string expected;
	expected += "position:    {x: -0.100000, y: 1.200000, z: 2.300000}\n"; //NOLINT
	expected += "orientation: {x: 0.000000, y: 0.000000, z: 0.000000, w: 1.000000}"; //NOLINT
	ASSERT_EQ(expected, toYaml(Eigen::Isometry3d{Eigen::Translation3d{-0.1, 1.2, 2.3} * Eigen::Quaterniond{1, 0, 0, 0}})); //NOLINT

	expected = "";
	expected += "\tposition:    {x: -0.100000, y: 1.200000, z: 2.300000}\n"; //NOLINT
	expected += "\torientation: {x: 0.000000, y: 0.000000, z: 0.000000, w: 1.000000}"; //NOLINT
	ASSERT_EQ(expected, toYaml(Eigen::Isometry3d{Eigen::Translation3d{-0.1, 1.2, 2.3} * Eigen::Quaterniond{1, 0, 0, 0}}, "\t")); //NOLINT
}

} //namespace dr
