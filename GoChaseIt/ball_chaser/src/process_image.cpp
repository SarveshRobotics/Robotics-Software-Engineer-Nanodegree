#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

using namespace std;

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot
// in the specified direction
void drive_robot(float lin_x, float ang_z){
	// TODO: Request a service and pass the velocities 
	// to it to drive the robot
// 	std::string isMoving;
// 	std::string direction;
	
// 	if (lin_x != 0)
// 		isMoving = "Moving Forward";
// 	else
// 		isMoving = "Not Moving Forward and ";

// 	if (isMoving == "Moving Forward"){
// 		if (ang_z == 0)
// 			direction = "!";
// 		else if (ang_z > 0)
// 			direction = "Left";
// 		else
// 			direction = "Right";
// 	}
// 	else
// 		direction = "Not Turning!";

	ROS_INFO_STREAM("Vehicle Update: Linear_X: "<< lin_x <<" & Angular_Z:  "<< ang_z);
	ball_chaser::DriveToTarget srv;
	srv.request.linear_x = lin_x;
	srv.request.angular_z = ang_z;

	// Call the command_robot service and pass the requested velocities
	if (!client.call(srv))
		ROS_ERROR("Failed to call the command_robot service!");
}


// This callback function continously reads and process the image data
void process_image_callback(const sensor_msgs::Image img){
// 	int white_pixel = 255;
	bool isWhite = false;
	int row;
	int col;
	for (int i=0; i<img.height*img.step; i+=3){
		if (img.data[i] == 255 and img.data[i+1] == 255 and img.data[i+2] == 255){// B, G, R all channel values of a pixel are 255?
			isWhite = true; // We have found a white pixel
			row = i/img.step;	// Position(vertical) of the ball in the image.
			col = (i%img.step)/3;	// Position(horizontal) of the ball in the image.
			break;
		}
	}
	
	if (isWhite == true){		
		if (col >= 0 and col <img.width/3)
			drive_robot(0.1, 0.2);
		else if (col >= img.width/3 and col < 2*img.width/3)
			drive_robot(0.5, 0);
		else if (col >= 2*img.width/3 and col < img.width)
			drive_robot(0.1, -0.2);
	}

	else
		drive_robot(0,0);
}


// ---------------------------------------------------------------

int main(int argc, char** argv)
{

	// Initialize the process_image node and create a handle to it
	ros::init(argc, argv, "process_image");
	ros::NodeHandle n;

	// Define a client service capable of requesting services from command_robot
	client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

	// Subscribe to /camera/rgb/image_raw topic to read the image data
	// inside the process_image_callback function
	ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

	// Handle ROS communication events
	ros::spin();

	return 0;
}
