#include "eigen.hpp"
#include "test/compare.hpp"

#include <gtest/gtest.h>


int main(int argc, char * * argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

namespace dr {

TEST(BoxTest, makeCenteredBox) { //NOLINT
	Eigen::AlignedBox3d box;
	box = makeCenteredBox({1, 2, 3}, {4, 5, 6}); //NOLINT

	ASSERT_EQ(Eigen::Vector3d( 1,  2.0, 3), box.center()); //NOLINT

	ASSERT_TRUE(testEqual(Eigen::Vector3d(-1, -0.5, 0), box.corner(Eigen::AlignedBox3d::BottomLeftFloor)));  //NOLINT
	ASSERT_TRUE(testEqual(Eigen::Vector3d(-1, -0.5, 6), box.corner(Eigen::AlignedBox3d::BottomLeftCeil)));   //NOLINT
	ASSERT_TRUE(testEqual(Eigen::Vector3d(-1,  4.5, 0), box.corner(Eigen::AlignedBox3d::TopLeftFloor)));     //NOLINT
	ASSERT_TRUE(testEqual(Eigen::Vector3d(-1,  4.5, 6), box.corner(Eigen::AlignedBox3d::TopLeftCeil)));      //NOLINT
	ASSERT_TRUE(testEqual(Eigen::Vector3d( 3, -0.5, 0), box.corner(Eigen::AlignedBox3d::BottomRightFloor))); //NOLINT
	ASSERT_TRUE(testEqual(Eigen::Vector3d( 3, -0.5, 6), box.corner(Eigen::AlignedBox3d::BottomRightCeil)));  //NOLINT
	ASSERT_TRUE(testEqual(Eigen::Vector3d( 3,  4.5, 0), box.corner(Eigen::AlignedBox3d::TopRightFloor)));    //NOLINT
	ASSERT_TRUE(testEqual(Eigen::Vector3d( 3,  4.5, 6), box.corner(Eigen::AlignedBox3d::TopRightCeil)));     //NOLINT
}
} //namespace dr
