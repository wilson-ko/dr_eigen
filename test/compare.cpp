#include "eigen.hpp"
#include "test/compare.hpp"

#include <gtest/gtest.h>

int main(int argc, char * * argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

namespace dr {

/// Test testEqual.
TEST(CompareTest, testEqual) { //NOLINT
	// Test equal is accepted.
	ASSERT_TRUE(testEqual(Eigen::Vector3d{1, 2, 3}, Eigen::Vector3d{1, 2, 3})); //NOLINT

	// Test small difference is rejected.
	ASSERT_FALSE(testEqual(Eigen::Vector3d{1.001, 2, 3}, Eigen::Vector3d{1, 2, 3})); //NOLINT

	// Test same elements different order is rejected.
	ASSERT_FALSE(testEqual(Eigen::Vector3d{3, 2, 1}, Eigen::Vector3d{1, 2, 3})); //NOLINT

	// Test single position differences are rejected.
	ASSERT_FALSE(testEqual(Eigen::Vector3d{1, 2, 3}, Eigen::Vector3d{1, 2, 0})); //NOLINT
	ASSERT_FALSE(testEqual(Eigen::Vector3d{1, 2, 3}, Eigen::Vector3d{1, 0, 3})); //NOLINT
	ASSERT_FALSE(testEqual(Eigen::Vector3d{1, 2, 3}, Eigen::Vector3d{0, 2, 3})); //NOLINT
}

/// Test testNear without precision argument.
TEST(CompareTest, testNearDefaultPrecision) { //NOLINT
	// Test equal.
	ASSERT_TRUE(testNear(Eigen::Vector3d{1, 2, 3}, Eigen::Vector3d{1, 2, 3})); //NOLINT

	// Test within precision.
	ASSERT_TRUE(testNear(Eigen::Vector3d{1, 2, 3}, Eigen::Vector3d{1.0005, 2.0005, 3.0005}));  //NOLINT
	ASSERT_TRUE(testNear(Eigen::Vector3d{1, 2, 3}, Eigen::Vector3d{0.9995, 1.9995, 2.9995}));  //NOLINT
	ASSERT_FALSE(testNear(Eigen::Vector3d{1, 2, 3}, Eigen::Vector3d{1.0015, 2.0015, 3.0015})); //NOLINT
	ASSERT_FALSE(testNear(Eigen::Vector3d{1, 2, 3}, Eigen::Vector3d{0.9985, 1.9985, 2.9985})); //NOLINT


	// Test same elements different order is rejected.
	ASSERT_FALSE(testNear(Eigen::Vector3d{3, 2, 1}, Eigen::Vector3d{1, 2, 3})); //NOLINT

	// Test single position differences are rejected.
	ASSERT_FALSE(testNear(Eigen::Vector3d{1, 2, 3}, Eigen::Vector3d{1, 2, 0})); //NOLINT
	ASSERT_FALSE(testNear(Eigen::Vector3d{1, 2, 3}, Eigen::Vector3d{1, 0, 3})); //NOLINT
	ASSERT_FALSE(testNear(Eigen::Vector3d{1, 2, 3}, Eigen::Vector3d{0, 2, 3})); //NOLINT
}


/// Test testNear with precision argument.
TEST(CompareTest, testNearCustomPrecision) { //NOLINT
	// TODO(@de-vri-es)
}

/// Test testNear for isometries
TEST(CompareTest, testNearDefaultPrecisionIsometry) { //NOLINT
	ASSERT_TRUE(
		testNear(
			Eigen::Isometry3d(Eigen::Translation3d{1, 2, 3} * Eigen::Quaterniond{0.707, 0.707, 0, 0}), //NOLINT
			Eigen::Isometry3d(Eigen::Translation3d{1, 2, 3} * Eigen::Quaterniond{0.707, 0.707, 0, 0}) //NOLINT
		)
	);

	ASSERT_FALSE(
		testNear(
			Eigen::Isometry3d(Eigen::Translation3d{1, 2, 3} * Eigen::Quaterniond{1, 0, 0, 0}), //NOLINT
			Eigen::Isometry3d(Eigen::Translation3d{1, 2, 3} * Eigen::Quaterniond{0, 1, 0, 0}) //NOLINT
		)
	);

	ASSERT_FALSE(
		testNear(
			Eigen::Isometry3d(Eigen::Translation3d{1, 2, 3} * Eigen::Quaterniond{0, 1, 0, 0}), //NOLINT
			Eigen::Isometry3d(Eigen::Translation3d{0, 2, 3} * Eigen::Quaterniond{0, 1, 0, 0}) //NOLINT
		)
	);
}

} //namespace dr
