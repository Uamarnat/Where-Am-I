#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>
#include <boost/algorithm/cxx11/any_of.hpp>
#include <vector>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
	//ROS_INFO("Drive bot function called");
	ball_chaser::DriveToTarget srv;
	srv.request.linear_x = lin_x;
	srv.request.angular_z = ang_z;

	if (!client.call(srv)) 
		ROS_ERROR("failed to call Drive bot service");

}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image& img)
{

    int white_pixel = 255;

    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera
	bool exist = boost::algorithm::any_of_equal(img.data, white_pixel);
	if(exist){	 
		for (int i = 0; i<img.height * img.step; i+=3){
			//ROS_INFO("Pixel value: %1.2f, pixel number %1.2f", (float)img.data[i], (float)i);		
			if(img.data[i] == white_pixel && img.data[i+1] == white_pixel && img.data[i+2] == white_pixel){
				if(i%img.step < img.step*0.4){
					drive_robot(0.5, 1.0); //Left
					break;
				}
				else if(i%img.step > img.step* 0.6){
					drive_robot(0.5, -1.0); //Right
					break;
				}
				else{
					drive_robot(0.5, 0.0); //Mid
					break;
				}
			}
			
		}
	}
	else
		drive_robot(0.0, 0.0);
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
