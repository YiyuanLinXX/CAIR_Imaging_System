
#include <ros/ros.h> 
#include <fcntl.h>
#include <termios.h>
#include<errno.h>
#include <iostream>
#include <serial/serial.h> 

#include <stdlib.h>
#include <stdio.h>
#include <std_msgs/String.h> 

#include <std_msgs/Empty.h> 

#include <sstream> 
#include <unistd.h>
using namespace std;

/*
serial::Serial ser; 
const std::string eol = "\r\n";
const size_t max_line_length = 128;
  

void write_callback(const std_msgs::String::ConstPtr& msg){ 

    //ROS_INFO_STREAM("Writing to serial port" << msg->data); 

    ser.write(msg->data); 

} 
*/
  

int main (int argc, char** argv){ 

    ros::init(argc, argv, "serial_example_node"); 

    ros::NodeHandle nh; 

  

    ros::Subscriber write_sub = nh.subscribe("read", 1, write_callback); 

    ros::Publisher read_pub = nh.advertise<std_msgs::String>("read", 1); 


    serial::Timeout to = serial::Timeout::simpleTimeout(500); 

    ser.setTimeout(to);
    
    ser.setPort("/dev/ttyACM0"); 

    ser.setBaudrate(9600);     
  

    try 

    { 

        ser.open();
        ROS_INFO("port opened");

    } 

    catch (serial::IOException& e) 

    { 

        ROS_ERROR_STREAM("Unable to open port /dev/ttyACM0"); 

        return -1; 

    } 

  

    if(ser.isOpen()){ 

        ROS_INFO_STREAM("Serial Port initialized: "<<ser.available()); 

    }else{ 

        return -1; 

    } 

  

    ros::Rate loop_rate(100); 

    int count = 0; 

    while(ros::ok()){ 

  

        //ros::spinOnce(); 

        if(!ser.isOpen()){
          ROS_WARN("Port not open!!");
        }

        if(ser.isOpen() ){ 

            //ROS_INFO_STREAM("Reading from serial port: "<< ser.available()); 

            std_msgs::String result;
            std_msgs::String enable_pin;
            std::stringstream ss;
            std::stringstream ss2;
            ss << "gpio set 4\r";
            //result.data = ser.readline(max_line_length, eol);        
            enable_pin.data = ss.str();

            //ROS_INFO_STREAM("Read: " << result.data<< count); 

            read_pub.publish(enable_pin); 
            sleep(1);
            ss2 << "gpio clear 4\r"; 

            enable_pin.data = ss2.str(); 

            read_pub.publish(enable_pin); 
            
            count++;

        } 
        ros::spinOnce();
        loop_rate.sleep(); 

  

    } 

} 

 
