
#include <ros/ros.h> 
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <iostream>
#include <serial/serial.h> 

#include <stdlib.h>
#include <stdio.h>
#include <std_msgs/String.h> 

#include <std_msgs/Empty.h> 

#include <sstream> 
#include <unistd.h>
#include <chrono>
#include <thread>



serial::Serial ser; 
const std::string eol = "\r\n";
const size_t max_line_length = 128;
  

void write_callback(const std_msgs::String::ConstPtr& msg){ 

    //ROS_INFO_STREAM("Writing to serial port" << msg->data); 

    ser.write(msg->data); 

} 

  

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
ser.write("gpio set 0\r");
ser.write("gpio clear 0\r");
ser.write("gpio set 1\r");
ser.write("gpio clear 1\r");

ser.write("gpio set 2\r");
ser.write("gpio clear 2\r");
ser.write("gpio set 3\r");
ser.write("gpio clear 3\r");
ser.write("gpio set 4\r");
ser.write("gpio clear 4\r");

    while(ros::ok()){ 

  

        //ros::spinOnce(); 

        if(!ser.isOpen()){
          ROS_WARN("Port not open!!");
        }

        if(ser.isOpen() ){ 

            //ROS_INFO_STREAM("Reading from serial port: "<< ser.available()); 

            std_msgs::String result;
            std_msgs::String enable_pin;
            std_msgs::String clear_pin;
            std::stringstream ss;
            std::stringstream ss2;
            ss << "gpio set \r";
            //result.data = ser.readline(max_line_length, eol);        
            enable_pin.data = ss.str();

            //ROS_INFO_STREAM("Read: " << result.data<< count); 
	    //cout<<"press enter to set 4";
            //getchar();
            //read_pub.publish(enable_pin); 
           /*
            ser.write("gpio writeall 00\r");
            //read_pub.publish(enable_pin);
            
            
            usleep(500);
            //ss2 << "gpio clear 4\r"; 

            //clear_pin.data = ss2.str(); 

	    //cout<<"press enter to clear 4";
            //getchar();
            ser.write("gpio writeall ff\r");
            //read_pub.publish(clear_pin); 
            //read_pub.publish(clear_pin); 
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            */
            /*
            ser.write("gpio clear 0\r");
            ser.write("gpio set 4\r"); // start discharging
            std::this_thread::sleep_for(std::chrono::microseconds(1000));//  1ms
            ser.write("gpio clear 4\r"); //stop discharging 
            
            std::this_thread::sleep_for(std::chrono::microseconds(500));//  500 us
            ser.write("gpio set 0\r"); // 
            std::this_thread::sleep_for(std::chrono::milliseconds(250));//  1ms
*/

	    ser.write("gpio writeall ee\r");  // 1111 1100 11101110
            std::this_thread::sleep_for(std::chrono::microseconds(1000));//  1ms
            //ser.write("gpio writeall 02\r"); //start discharging 0000 0010    00010000
            ser.write("gpio writeall 10\r"); //start discharging 0000 0010    00010000
            std::this_thread::sleep_for(std::chrono::microseconds(1000));//  500 us
            //ser.write("gpio writeall fc\r"); // stop discharging 11111100     11101110
            ser.write("gpio writeall ee\r"); // stop discharging 11101110
            std::this_thread::sleep_for(std::chrono::microseconds(1000));//  1ms
            ser.write("gpio writeall ef\r"); // start charging 11111101       11101111
            
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            
            count++;
            //cout<<"press enter to the next loop";
            //getchar();

        } 
        ros::spinOnce();
        loop_rate.sleep(); 

  

    } 

} 

 
