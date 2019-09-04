#include "eigen.hpp"
#include "plane.hpp"
#include "test/compare.hpp"

#include <gtest/gtest.h>


int main(int argc, char * * argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

namespace dr {

namespace {
	double pi = 3.1415926536; //NOLINT
} //namespace

TEST(PlaneTest, makePlaneFromVectors) { //NOLINT
	Eigen::Hyperplane<double, 3> plane;

	plane = makePlane({0, 0, 1}, {0, 0, 2}); //NOLINT
	ASSERT_TRUE(testEqual(axes::z(), plane.normal()));
	ASSERT_DOUBLE_EQ(-2, plane.offset()); //NOLINT

	plane = makePlane({0, 1, 0}, {0, -2, 0}); //NOLINT
	ASSERT_TRUE(testEqual(axes::y(), plane.normal()));
	ASSERT_DOUBLE_EQ(2, plane.offset()); //NOLINT

	plane = makePlane({-1, 0, 0}, {5, 0, 0}); //NOLINT
	ASSERT_TRUE(testEqual(-axes::x(), plane.normal()));
	ASSERT_DOUBLE_EQ(5, plane.offset()); //NOLINT
}

TEST(PlaneTest, makeXyPlane) { //NOLINT
	Eigen::Hyperplane<double, 3> plane;

	plane = makeXyPlane(translate(1, 2, 3) * rotateX(0.5 * pi)); //NOLINT
	ASSERT_TRUE(testNear(-axes::y(), plane.normal()));
	ASSERT_DOUBLE_EQ(0, plane.signedDistance(Eigen::Vector3d(1, 2, 3))); //NOLINT
}

TEST(PlaneTest, vectorRejection) { //NOLINT
	ASSERT_TRUE(testNear({5, 0, 0}, rejection(Eigen::Vector3d{4, 5, 6}, Eigen::Hyperplane<double, 3>{{1, 0, 0}, 1}))); //NOLINT
	ASSERT_TRUE(testNear({0, -3, 0}, rejection(Eigen::Vector3d{4, 5, 6}, Eigen::Hyperplane<double, 3>{{0, -1, 0}, 8}))); //NOLINT
	ASSERT_TRUE(testNear({0, 0, 9}, rejection(Eigen::Vector3d{4, 5, 6}, Eigen::Hyperplane<double, 3>{{0, 0, 1}, 3}))); //NOLINT
}

TEST(PlaneTest, vectorReflection) { //NOLINT
	Eigen::Hyperplane<double, 3> plane;
	ASSERT_TRUE(testNear({-6, 5, 6}, reflection(Eigen::Vector3d{4, 5, 6}, Eigen::Hyperplane<double, 3>{{1, 0, 0}, 1}))); //NOLINT
	ASSERT_TRUE(testNear({4, 11, 6}, reflection(Eigen::Vector3d{4, 5, 6}, Eigen::Hyperplane<double, 3>{{0, -1, 0}, 8}))); //NOLINT
	ASSERT_TRUE(testNear({4, 5, -12}, reflection(Eigen::Vector3d{4, 5, 6}, Eigen::Hyperplane<double, 3>{{0, 0, 1}, 3}))); //NOLINT
}

} //namespace dr
