#pragma once

#include "ros.hpp"
#include <visualization_msgs/Marker.h>

namespace dr {

inline visualization_msgs::Marker toMarker(
	Eigen::AlignedBox3d const & box,
	Eigen::Isometry3d   const & pose,
	Eigen::Vector4d     const & rgba,
	std::string         const & ns       = "",
	std::string         const & frame_id = "",
	ros::Time           const & time     = ros::Time::now()
) {
	visualization_msgs::Marker marker;
	marker.header.frame_id = frame_id;
	marker.header.stamp    = time;
	marker.ns              = ns;
	marker.type            = visualization_msgs::Marker::CUBE;
	marker.pose            = toRosPose(pose);
	marker.scale           = toRosVector3(box.sizes());
	marker.color.r         = rgba(0);
	marker.color.g         = rgba(1);
	marker.color.b         = rgba(2);
	marker.color.a         = rgba(3);

	return marker;
}

}
