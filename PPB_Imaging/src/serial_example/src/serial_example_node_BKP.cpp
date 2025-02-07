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

  

    ros::Subscriber write_sub = nh.subscribe("write", 1, write_callback); 

    ros::Publisher read_pub = nh.advertise<std_msgs::String>("write", 1); 


    serial::Timeout to = serial::Timeout::simpleTimeout(500); 

    ser.setTimeout(to);
    
    ser.setPort("/dev/ttyUSB1"); 

    ser.setBaudrate(9600);     
  

    try 

    { 

        ser.open();
        ROS_INFO("port opened");

    } 

    catch (serial::IOException& e) 

    { 

        ROS_ERROR_STREAM("Unable to open port /dev/ttyUSB1"); 

        return -1; 

    } 

  

    if(ser.isOpen()){ 

        ROS_INFO_STREAM("Serial Port initialized: "<<ser.available()); 

    }else{ 

        return -1; 

    } 

  

    ros::Rate loop_rate(1); 

    int count = 0; 

    while(ros::ok() && count<=20){ 

  

        ros::spinOnce(); 

        if(!ser.isOpen()){
          ROS_WARN("Port not open!!");
        }

        if(ser.isOpen()){ 

            ROS_INFO_STREAM("Reading from serial port: "<< ser.available()); 

            std_msgs::String result; 

            std::stringstream ss; 

            if(count<1) 

            ss<<"EIGN(W,0) "; 

            /*if(count>2 & count<=3) 

            ss<<"ZS ";*/ 

            /*if(count<=2 && count>1) 

            ss<<"ZS ";*/ 

            if(count>2 && count<=3) 

            ss<<"ZS MT T=2000 G "; 

            if(count>=19) 

            ss<<"OFF "; 

            result.data = ss.str(); 

            ROS_INFO_STREAM("Read: " << result.data<< count); 

            read_pub.publish(result); 

            count++; 

        } 

        loop_rate.sleep(); 

  

    } 

} 

 
