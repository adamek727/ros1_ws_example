#include <sstream>
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/Float32.h>

visualization_msgs::Marker createCuteCube(float pose) {

    visualization_msgs::Marker marker;
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time();
    marker.ns = "cube";

    marker.id = 0;
    marker.type = visualization_msgs::Marker::CUBE;
    marker.action = visualization_msgs::Marker::ADD;

    marker.pose.position.x = sin(pose);
    marker.pose.position.y = cos(pose);
    marker.pose.position.z = 0.1*sin(5*pose);

    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    marker.scale.x = 0.1;
    marker.scale.y = 0.1;
    marker.scale.z = 0.1;

    marker.color.a = 1.0;
    marker.color.r = 0.0;
    marker.color.g = 1.0;
    marker.color.b = 0.0;

    return marker;
}


int main(int argc, char **argv) {

    ros::init(argc, argv, "cpp_rviz_publisher");
    ros::NodeHandle n;

    ros::Publisher vis_pub = n.advertise<visualization_msgs::Marker>( "/cute_cube", 0 );
    ros::Publisher scalar_pub = n.advertise<std_msgs::Float32>("/my_scalar",0);

    ros::Rate loop_rate(100);

    float pose = 0;
    while (ros::ok()) {
        visualization_msgs::Marker cube = createCuteCube(pose);
        vis_pub.publish( cube );
	
	auto scalar_msg = std_msgs::Float32();
	scalar_msg.data = cube.pose.position.x;
	scalar_pub.publish(scalar_msg);
        pose += 0.01;

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
