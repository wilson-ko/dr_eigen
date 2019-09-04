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
TEST(EigenParamQuaternion, validDouble) { //NOLINT
	XmlRpc::XmlRpcValue quaterion;
	quaterion["w"] = double(1.0); //NOLINT
	quaterion["x"] = double(2.0); //NOLINT
	quaterion["y"] = double(3.0); //NOLINT
	quaterion["z"] = double(4.0); //NOLINT

	ASSERT_NEAR(0, fromXmlRpc<Eigen::Quaterniond>(quaterion).angularDistance(Eigen::Quaterniond{1, 2, 3, 4}), 1e-5); //NOLINT
}

// Parse a quaterion from ints.
TEST(EigenParamQuaternion, validInt) { //NOLINT
	XmlRpc::XmlRpcValue quaterion;
	quaterion["w"] = int(1); //NOLINT
	quaterion["x"] = int(2); //NOLINT
	quaterion["y"] = int(3); //NOLINT
	quaterion["z"] = int(4); //NOLINT

	ASSERT_NEAR(0, fromXmlRpc<Eigen::Quaterniond>(quaterion).angularDistance(Eigen::Quaterniond{1, 2, 3, 4}), 1e-5); //NOLINT
}

// Parse a quaterion from mixed doubles and ints.
TEST(EigenParamQuaternion, validMixed) { //NOLINT
	XmlRpc::XmlRpcValue quaterion;
	quaterion["w"] = double(1.0); //NOLINT
	quaterion["x"] = int(2); //NOLINT
	quaterion["y"] = double(3.0); //NOLINT
	quaterion["z"] = int(4); //NOLINT

	ASSERT_NEAR(0, fromXmlRpc<Eigen::Quaterniond>(quaterion).angularDistance(Eigen::Quaterniond{1, 2, 3, 4}), 1e-5); //NOLINT
}

// Test that parsing from a structure with too many components fails.
TEST(EigenParamQuaternion, tooManyComponents) { //NOLINT
	XmlRpc::XmlRpcValue quaterion;
	quaterion["v"] = 0.0; //NOLINT
	quaterion["w"] = 1.0; //NOLINT
	quaterion["x"] = 2.0; //NOLINT
	quaterion["y"] = 3.0; //NOLINT
	quaterion["z"] = 4.0; //NOLINT

	ASSERT_THROW(fromXmlRpc<Eigen::Quaterniond>(quaterion), std::exception); //NOLINT
}

// Test that parsing from a structure with too few components fails.
TEST(EigenParamQuaternion, missingComponents) { //NOLINT
	XmlRpc::XmlRpcValue quaterion;
	quaterion["x"] = 1.0; //NOLINT
	quaterion["y"] = 2.0; //NOLINT
	quaterion["z"] = 3.0; //NOLINT

	ASSERT_THROW(fromXmlRpc<Eigen::Quaterniond>(quaterion), std::exception); //NOLINT
}

// Test that parsing from a structure with wrongly named components fails.
TEST(EigenParamQuaternion, wrongComponents) { //NOLINT
	XmlRpc::XmlRpcValue quaterion;
	quaterion["aap"]  = 1.0; //NOLINT
	quaterion["noot"] = 2.0; //NOLINT
	quaterion["mies"] = 3.0; //NOLINT
	quaterion["wim"]  = 4.0; //NOLINT

	ASSERT_THROW(fromXmlRpc<Eigen::Quaterniond>(quaterion), std::exception); //NOLINT
}

} //namespace dr
