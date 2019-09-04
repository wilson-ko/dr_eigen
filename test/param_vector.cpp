#include "param.hpp"
#include "test/compare.hpp"

#include <gtest/gtest.h>
#include <exception>


int main(int argc, char * * argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

namespace dr {

// Parse a vector from doubles.
TEST(EigenParamVector, validDouble) { //NOLINT
	XmlRpc::XmlRpcValue vector;
	vector["x"] = double(1.0); //NOLINT
	vector["y"] = double(2.0); //NOLINT
	vector["z"] = double(3.0); //NOLINT

	ASSERT_TRUE(testEqual(Eigen::Vector3d{1, 2, 3}, fromXmlRpc<Eigen::Vector3d>(vector))); //NOLINT
}

// Parse a vector from ints.
TEST(EigenParamVector, validInt) { //NOLINT
	XmlRpc::XmlRpcValue vector;
	vector["x"] = int(1); //NOLINT
	vector["y"] = int(2); //NOLINT
	vector["z"] = int(3); //NOLINT

	ASSERT_TRUE(testEqual(Eigen::Vector3d{1, 2, 3}, fromXmlRpc<Eigen::Vector3d>(vector)));
}

// Parse a vector from mixed doubles and ints.
TEST(EigenParamVector, validMixed) { //NOLINT
	XmlRpc::XmlRpcValue vector;
	vector["x"] = double(1.0); //NOLINT
	vector["y"] = double(2.0); //NOLINT
	vector["z"] = int(3); //NOLINT

	ASSERT_TRUE(testEqual(Eigen::Vector3d{1, 2, 3}, fromXmlRpc<Eigen::Vector3d>(vector))); //NOLINT
}

// Test that parsing from a structure with too many components fails.
TEST(EigenParamVector, tooManyComponents) { //NOLINT
	XmlRpc::XmlRpcValue vector;
	vector["w"] = 0.0; //NOLINT
	vector["x"] = 1.0; //NOLINT
	vector["y"] = 2.0; //NOLINT
	vector["z"] = 3.0; //NOLINT

	ASSERT_THROW(fromXmlRpc<Eigen::Vector3d>(vector), std::exception); //NOLINT
}

// Test that parsing from a structure with too few components fails.
TEST(EigenParamVector, missingComponents) { //NOLINT
	XmlRpc::XmlRpcValue vector;
	vector["x"] = 1.0; //NOLINT
	vector["y"] = 2.0; //NOLINT

	ASSERT_THROW(fromXmlRpc<Eigen::Vector3d>(vector), std::exception); //NOLINT
}

// Test that parsing from a structure with wrongly named components fails.
TEST(EigenParamVector, wrongComponents) { //NOLINT
	XmlRpc::XmlRpcValue vector;
	vector["aap"]  = 1.0; //NOLINT
	vector["noot"] = 2.0; //NOLINT
	vector["mies"] = 3.0; //NOLINT

	ASSERT_THROW(fromXmlRpc<Eigen::Vector3d>(vector), std::exception); //NOLINT
}

} //namespace dr
