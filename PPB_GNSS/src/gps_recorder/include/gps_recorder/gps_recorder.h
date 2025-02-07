#ifndef GPS_RECORDER_H
#define GPS_RECORDER_H

#include <ros/ros.h>
#include <sensor_msgs/NavSatFix.h>
#include <fstream>
#include <iomanip>
#include <boost/filesystem.hpp>
#include <cstdlib>  // For getenv
#include <ctime>
#include <chrono>
#include <sstream>

class GpsRecorder
{
public:
    GpsRecorder(ros::NodeHandle& nh);
    ~GpsRecorder();

private:
    void gpsCallback(const sensor_msgs::NavSatFix::ConstPtr& msg);
    std::string getCurrentDateTime();

    ros::Subscriber gps_sub_;


    std::string folder_name_;
    std::string folder_loc_;
    std::ofstream gps_file_;
    bool gps_header_written_;
};

#endif // GPS_RECORDER_H