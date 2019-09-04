#include "param.hpp"
#include "eigen.hpp"
#include "test/compare.hpp"

#include <gtest/gtest.h>
#include <exception>


int main(int argc, char * * argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

namespace dr {

// Parse a quaternion from doubles.
TEST(EigenParameterAlignedBox, validDouble) { //NOLINT
	XmlRpc::XmlRpcValue value;
	value["center"]["x"]     = double(1.0); //NOLINT
	value["center"]["y"]     = double(2.0); //NOLINT
	value["center"]["z"]     = double(3.0); //NOLINT
	value["dimensions"]["x"] = double(4.0); //NOLINT
	value["dimensions"]["y"] = double(5.0); //NOLINT
	value["dimensions"]["z"] = double(6.0); //NOLINT

	ASSERT_TRUE(fromXmlRpc<Eigen::AlignedBox3d>(value).isApprox(makeCenteredBox({1, 2, 3}, {4, 5, 6}))); //NOLINT
}

// Parse a value from ints.
TEST(EigenParameterAlignedBox, validInt) { //NOLINT
	XmlRpc::XmlRpcValue value;
	value["center"]["x"]     = int(1); //NOLINT
	value["center"]["y"]     = int(2); //NOLINT
	value["center"]["z"]     = int(3); //NOLINT
	value["dimensions"]["x"] = int(4); //NOLINT
	value["dimensions"]["y"] = int(5); //NOLINT
	value["dimensions"]["z"] = int(6); //NOLINT

	ASSERT_TRUE(fromXmlRpc<Eigen::AlignedBox3d>(value).isApprox(makeCenteredBox({1, 2, 3}, {4, 5, 6}))); //NOLINT
}

// Test that parsing from a structure with too many components fails.
TEST(EigenParameterAlignedBox, tooManyComponents) { //NOLINT
	XmlRpc::XmlRpcValue value;
	value["center"]["x"]     = double(1.0); //NOLINT
	value["center"]["y"]     = double(2.0); //NOLINT
	value["center"]["z"]     = double(3.0); //NOLINT
	value["dimensions"]["x"] = double(4.0); //NOLINT
	value["dimensions"]["y"] = double(5.0); //NOLINT
	value["dimensions"]["z"] = double(6.0); //NOLINT
	value["nonsense"]["x"]   = double(7.0); //NOLINT

	ASSERT_THROW(fromXmlRpc<Eigen::AlignedBox3d>(value), std::exception);
}

// Test that parsing from a structure with too few components fails.
TEST(EigenParameterAlignedBox, missingComponents) { //NOLINT
	XmlRpc::XmlRpcValue value;
	value["center"]["x"]     = double(1.0); //NOLINT
	value["center"]["y"]     = double(2.0); //NOLINT
	value["center"]["z"]     = double(3.0); //NOLINT

	ASSERT_THROW(fromXmlRpc<Eigen::AlignedBox3d>(value), std::exception);
}

// Test that parsing from a structure with wrongly named components fails.
TEST(EigenParameterAlignedBox, wrongComponents) { //NOLINT
	XmlRpc::XmlRpcValue value;
	value["nonsense"]["x"]     = double(1.0); //NOLINT
	value["nonsense"]["y"]     = double(2.0); //NOLINT
	value["nonsense"]["z"]     = double(3.0); //NOLINT
	value["garbage"]["x"]      = double(4.0); //NOLINT
	value["garbage"]["y"]      = double(5.0); //NOLINT
	value["garbage"]["z"]      = double(6.0); //NOLINT

	ASSERT_THROW(fromXmlRpc<Eigen::AlignedBox3d>(value), std::exception);
}

} //namespace dr
