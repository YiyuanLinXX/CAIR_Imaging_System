/*** 

* This example expects the serial port has a loopback on it. 

* 

* Alternatively, you could use an Arduino: 

* 

* <pre> 

*  void setup() { 

*    Serial.begin(<insert your baudrate here>); 

*  } 

* 

*  void loop() { 

*    if (Serial.available()) { 

*      Serial.write(Serial.read()); 

*    } 

*  } 

* </pre> 

*/ 

  

#include <ros/ros.h> 

#include <serial/serial.h> 

#include <std_msgs/String.h> 

#include <std_msgs/Empty.h> 

#include <sstream> 

  

serial::Serial ser; 

  

void write_callback(const std_msgs::String::ConstPtr& msg){ 

    ROS_INFO_STREAM("Writing to serial port" << msg->data); 

    ser.write(msg->data); 

} 

  

int main (int argc, char** argv){ 

    ros::init(argc, argv, "serial_example_node"); 

    ros::NodeHandle nh; 

    serial::Timeout to = serial::Timeout::simpleTimeout(500); 

    ser.setTimeout(to);
    
    ser.setPort("/dev/ttyUSB0"); 

    ser.setBaudrate(9600);     
  

    try 

    { 

        ser.open();
        ROS_INFO("port opened");

    } 

    catch (serial::IOException& e) 

    { 

        ROS_ERROR_STREAM("Unable to open port /dev/ttyS0"); 

        return -1; 

    } 

  

    if(ser.isOpen()){ 

        ROS_INFO_STREAM("Serial Port initialized: "<<ser.available()); 

    }else{ 
        ROS_INFO_STREAM("Serial Port cannot open "<<ser.available());

        return -1; 

    }     

} 

 
