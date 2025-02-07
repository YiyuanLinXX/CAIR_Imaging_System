#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include "paramListener.h"
#include <boost/algorithm/string.hpp>
#include <map>
#include <errno.h>

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */

#include <stdio.h>
#include <unistd.h>

#include "flirBFS.h"


void exposureTimeCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard exposureTime: [%s]", msg->data.c_str());
}

void exposureAutoCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard exposureAuto: [%s]", msg->data.c_str());
}

void triggerModeCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard triggerMode: [%s]", msg->data.c_str());
}

void triggerSourceCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard triggerSource: [%s]", msg->data.c_str());
}

void pixelFormatCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard pixelFormat: [%s]", msg->data.c_str());
}

void gainAutoCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard gainAuto: [%s]", msg->data.c_str());
}

void balanceWhiteAutoCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard balanceWhiteAuto: [%s]", msg->data.c_str());
}

void gainCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard gain: [%s]", msg->data.c_str());
}


void chatter1(const std_msgs::Bool::ConstPtr& msg)
{
  ROS_INFO("I heard bool test : [%s]", msg->data ? "true" : "false");
}

void test(){

  cout<<"test the web server\n";

  ros::NodeHandle n;

  ros::Subscriber sub1 = n.subscribe("exposureAuto", 1000, exposureAutoCallback);

  ros::Subscriber sub = n.subscribe("exposureTime", 1000, exposureTimeCallback);

  ros::Subscriber sub3 = n.subscribe("triggerMode", 1000, triggerModeCallback);

  ros::Subscriber sub4 = n.subscribe("triggerSource", 1000, triggerSourceCallback);

  ros::Subscriber sub5 = n.subscribe("pixelFormat", 1000, pixelFormatCallback);

  ros::Subscriber sub6 = n.subscribe("gainAuto", 1000, gainAutoCallback);

  ros::Subscriber sub8 = n.subscribe("balanceWhiteAuto", 1000, balanceWhiteAutoCallback);

  ros::Subscriber sub7 = n.subscribe("gain", 1000, gainCallback);

  ros::spin();
}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "camera_listener");

  //test();

  ros::NodeHandle nh("~");

  ROS_INFO("main: instantiating an object of type Param_listener");
  Param_listener param_listener(&nh);

 // cout<<"params_rev.size(): "<<param_listener.params_rev.size()<<endl;

  ROS_INFO("main: going into spin; let the callbacks do all the work");
//  ros::spin();

  ros::MultiThreadedSpinner spinner(4);
  spinner.spin();


/*
  while(ros::ok()){

      ros::spinOnce();

      //cout<<"params_rev.size(): "<<param_listener.params_rev.size()<<endl;

      //break;
  }*/

}
