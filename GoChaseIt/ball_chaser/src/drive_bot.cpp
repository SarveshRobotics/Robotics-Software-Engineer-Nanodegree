#include <string>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"	//TODO: Include the ball_chaser 
					// "DriveToTarget" header file

using namespace std;

// ROS::Publisher motor commands; Declaring as a global variable
ros::Publisher motor_command_publisher;

// TODO: Create a handle_drive_request callback function that executes 
// whenever a drive_bot service is requested. This function should publish 
// the requested linear x and angular velocities to the robot wheel joints
// After publishing the requested velocities, a message feedback should 
// be returned with the requested wheel velocities
bool handle_drive_request(ball_chaser::DriveToTarget::Request& req, ball_chaser::DriveToTarget::Response& res)
{
	ROS_INFO("DriveToTargetRequest received - Linear_x:%1.2f, Angular_z:%1.2f", (float)req.linear_x, (float)req.angular_z);
	
	// OverKill - Creating a new variable to store the req params.
	geometry_msgs::Twist motor_command;

	// Set wheel velocities
	motor_command.linear.x = req.linear_x;
	motor_command.angular.z = req.angular_z;


	// Publishing Angles to drive the robot.
	motor_command_publisher.publish(motor_command);

	// Wait 100ms for the bot to settle
	// ros::Duration(0.1).sleep();

	// Return a response message
	res.msg_feedback = "Setting Velocities: linear_x: " + std::to_string(motor_command.linear.x) + " , angular_z: " + std::to_string(motor_command.angular.z);
	ROS_INFO_STREAM(res.msg_feedback);

	return true;
}



// ++++++++++++++++++++++++++++++++++++++++++++++

int main(int argc, char** argv){

	// Initialize a ROS node
	ros::init(argc, argv, "drive_bot");

	// Create a ROS NodeHandle Object
	ros::NodeHandle n;

	// Inform ROS master that we will be publishing a message of
	// type: geometry_msgs::Twist on the robot actuation topic with
	// a publishing queue size of 10. For this we create a publisher
	// object
	motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

	// TODO: Define a drive /ball_chaser/command_robot service with a 
	// handle_drive_request callback function
	ros::ServiceServer service = n.advertiseService("/ball_chaser/command_robot", handle_drive_request);

	ROS_INFO("Ready to send Velocity Commands!");

	// TODO: Handle ROS communication events
	ros::spin();

	return 0;
}
