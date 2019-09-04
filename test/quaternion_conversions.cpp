#include "ros.hpp"
#include "test/compare.hpp"

#include <gtest/gtest.h>


int main(int argc, char * * argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

namespace dr {

void quaternionAssertNear(const Eigen::Quaterniond & real_quaternion, const Eigen::Quaterniond & converted_quaternion) {

	ASSERT_NEAR(converted_quaternion.w(), real_quaternion.w(), 1e-5); //NOLINT
	ASSERT_NEAR(converted_quaternion.y(), real_quaternion.y(), 1e-5); //NOLINT
	ASSERT_NEAR(converted_quaternion.z(), real_quaternion.z(), 1e-5); //NOLINT
	ASSERT_NEAR(converted_quaternion.x(), real_quaternion.x(), 1e-5); //NOLINT
}

void rpyAssertNear(const Eigen::Vector3d & real_rpy, const Eigen::Vector3d & converted_rpy) {
	ASSERT_NEAR(converted_rpy[0], real_rpy[0], 1e-5); //NOLINT
	ASSERT_NEAR(converted_rpy[1], real_rpy[1], 1e-5); //NOLINT
	ASSERT_NEAR(converted_rpy[2], real_rpy[2], 1e-5); //NOLINT
}

void testConversion(const Eigen::Quaterniond & quaternion, const Eigen::Vector3d & rpy) {
	quaternionAssertNear(quaternion, rpyToQuaternion(rpy));
	rpyAssertNear(rpy, quaternionToRpy(quaternion));

	quaternionAssertNear(quaternion, rpyToQuaternion(quaternionToRpy(quaternion)));
	rpyAssertNear(rpy, quaternionToRpy(rpyToQuaternion(rpy)));
}

void testConversion(const Eigen::AngleAxisd & quaternion, const Eigen::Vector3d & rpy) {
	testConversion(Eigen::Quaterniond{quaternion}, rpy);
}

TEST(quaternionConversions, identity) { //NOLINT
	testConversion(Eigen::Quaterniond::Identity(), {0, 0, 0}); //NOLINT
}

TEST(quaternionConversions, yaw) { //NOLINT
	testConversion(rotateZ(0.5), {0, 0, 0.5}); //NOLINT
}

TEST(quaternionConversions, pitch) { //NOLINT
	testConversion(rotateY(0.5), {0, 0.5, 0}); //NOLINT
}

TEST(quaternionConversions, roll) { //NOLINT
	testConversion(rotateX(0.5), {0.5, 0, 0}); //NOLINT
}

TEST(quaternionConversions, rpy) { //NOLINT
	testConversion(rotateZ(0.1) * rotateY(0.2) * rotateX(0.5), {0.5, 0.2, 0.1}); //NOLINT
}

} //namespace dr
