#include "param.hpp"
#include "test/compare.hpp"

#include <gtest/gtest.h>
#include <exception>


int main(int argc, char * * argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

namespace dr {

// Parse a quaternion from doubles.
TEST(EigenParamIsometry, validDouble) { //NOLINT
	XmlRpc::XmlRpcValue value;
	value["position"]["x"]    = double(1.0); //NOLINT
	value["position"]["y"]    = double(2.0); //NOLINT
	value["position"]["z"]    = double(3.0); //NOLINT
	value["orientation"]["w"] = double(-0.5); //NOLINT
	value["orientation"]["x"] = double(0.5); //NOLINT
	value["orientation"]["y"] = double(0.5); //NOLINT
	value["orientation"]["z"] = double(0.5); //NOLINT

	Eigen::Isometry3d converted = fromXmlRpc<Eigen::Isometry3d>(value);
	Eigen::Quaterniond orientation = Eigen::Quaterniond{converted.rotation()};

	ASSERT_EQ(Eigen::Vector3d(1, 2, 3), converted.translation()); //NOLINT
	ASSERT_DOUBLE_EQ(-0.5, orientation.w()); //NOLINT
	ASSERT_DOUBLE_EQ(0.5, orientation.x()); //NOLINT
	ASSERT_DOUBLE_EQ(0.5, orientation.y()); //NOLINT
	ASSERT_DOUBLE_EQ(0.5, orientation.z()); //NOLINT
}

// Parse a value from ints.
TEST(EigenParamIsometry, validInt) { //NOLINT
	XmlRpc::XmlRpcValue value;
	value["position"]["x"]    = int(1); //NOLINT
	value["position"]["y"]    = int(2); //NOLINT
	value["position"]["z"]    = int(3); //NOLINT
	value["orientation"]["w"] = int(1); //NOLINT
	value["orientation"]["x"] = int(0); //NOLINT
	value["orientation"]["y"] = int(0); //NOLINT
	value["orientation"]["z"] = int(0); //NOLINT

	Eigen::Isometry3d converted = fromXmlRpc<Eigen::Isometry3d>(value);
	Eigen::Quaterniond orientation = Eigen::Quaterniond{converted.rotation()};

	ASSERT_EQ(Eigen::Vector3d(1, 2, 3), converted.translation()); //NOLINT
	ASSERT_DOUBLE_EQ(1, orientation.w()); //NOLINT
	ASSERT_DOUBLE_EQ(0, orientation.x()); //NOLINT
	ASSERT_DOUBLE_EQ(0, orientation.y()); //NOLINT
	ASSERT_DOUBLE_EQ(0, orientation.z()); //NOLINT
}

// Test that parsing from a structure with too many components fails.
TEST(EigenParamIsometry, tooManyComponents) { //NOLINT
	XmlRpc::XmlRpcValue value;
	value["nonsense"]["a"]    = double(1.0); //NOLINT
	value["position"]["x"]    = double(1.0); //NOLINT
	value["position"]["y"]    = double(2.0); //NOLINT
	value["position"]["z"]    = double(3.0); //NOLINT
	value["orientation"]["w"] = double(-0.5); //NOLINT
	value["orientation"]["x"] = double(0.5); //NOLINT
	value["orientation"]["y"] = double(0.5); //NOLINT
	value["orientation"]["z"] = double(0.5); //NOLINT

	ASSERT_THROW(fromXmlRpc<Eigen::Isometry3d>(value), std::exception); //NOLINT
}

// Test that parsing from a structure with too few components fails.
TEST(EigenParamIsometry, missingComponents) { //NOLINT
	XmlRpc::XmlRpcValue value;
	value["position"]["x"]    = double(1.0); //NOLINT
	value["position"]["y"]    = double(2.0); //NOLINT
	value["position"]["z"]    = double(3.0); //NOLINT

	ASSERT_THROW(fromXmlRpc<Eigen::Isometry3d>(value), std::exception); //NOLINT
}

// Test that parsing from a structure with wrongly named components fails.
TEST(EigenParamIsometry, wrongComponents) { //NOLINT
	XmlRpc::XmlRpcValue value;
	value["nonsense"]["x"]      = double(1.0); //NOLINT
	value["nonsense"]["y"]      = double(2.0); //NOLINT
	value["nonsense"]["z"]      = double(3.0); //NOLINT
	value["more_nonsense"]["w"] = double(-0.5); //NOLINT
	value["more_nonsense"]["x"] = double(0.5); //NOLINT
	value["more_nonsense"]["y"] = double(0.5); //NOLINT
	value["more_nonsense"]["z"] = double(0.5); //NOLINT

	ASSERT_THROW(fromXmlRpc<Eigen::Isometry3d>(value), std::exception); //NOLINT
}

} //namespace dr
