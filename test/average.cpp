#include <gtest/gtest.h>

#include "average.hpp"
#include "test/compare.hpp"


int main(int argc, char * * argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

namespace dr {

TEST(AverageQuaternionTest, averageOrientations) { //NOLINT
	// Define orientations
	Eigen::Matrix3d m1;
	Eigen::Matrix3d m2;
	m1 = Eigen::AngleAxisd(0.25*M_PI, Eigen::Vector3d::UnitX()); //NOLINT
	m2 = Eigen::AngleAxisd(0.75*M_PI, Eigen::Vector3d::UnitX()); //NOLINT

	// Convert to quaternions
	std::vector<Eigen::Quaterniond> orientations;
	orientations.emplace_back( Eigen::Quaterniond(m1) );
	orientations.emplace_back( Eigen::Quaterniond(m2) );
	
	Eigen::Quaterniond actual = averageQuaternions<double>(orientations);
	Eigen::Quaterniond expected(Eigen::AngleAxisd(0.5*M_PI, Eigen::Vector3d::UnitX())); //NOLINT

	ASSERT_TRUE(testNear(Eigen::AngleAxisd(expected), Eigen::AngleAxisd(actual)));
}

TEST(AveragePositionTest, averagePositions) { //NOLINT
	// Define positions
	std::vector<Eigen::Vector3d> positions;
	positions.emplace_back(Eigen::Vector3d(0.1, 0.2, 0.3)); //NOLINT
	positions.emplace_back(Eigen::Vector3d(-0.6, 0.6, 0.7)); //NOLINT

	Eigen::Vector3d actual = averagePositions<double>(positions);
	Eigen::Vector3d expected(-0.25, 0.4, 0.5); //NOLINT

	ASSERT_TRUE(testNear(expected, actual));
}

TEST(AverageIsometryTest, averageIsometries) { //NOLINT
	std::vector<Eigen::Transform<double, 3, Eigen::Isometry>> isometries;
	isometries.emplace_back(Eigen::Translation<double, 3>(0,  1, 2.5) * Eigen::Quaternion<double>(1, 0, 0, 0)); //NOLINT
	isometries.emplace_back(Eigen::Translation<double, 3>(4, -2, 1  ) * Eigen::Quaternion<double>(0.70711, 0.70711, 0, 0)); //NOLINT

	Eigen::Transform<double, 3, Eigen::Isometry> actual   = averageIsometries<double>(isometries);
	Eigen::Transform<double, 3, Eigen::Isometry> expected = Eigen::Translation<double, 3>(2, -0.5, 1.75) * Eigen::Quaternion<double>(0.92388, 0.38268, 0, 0); //NOLINT

	ASSERT_TRUE(testNear(expected, actual));
}
} //namespace dr
