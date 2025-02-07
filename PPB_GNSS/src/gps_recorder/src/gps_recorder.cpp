#include "gps_recorder/gps_recorder.h"


GpsRecorder::GpsRecorder(ros::NodeHandle& nh): gps_header_written_(false)
{
  gps_sub_ = nh.subscribe("/robot/main_gps_fix", 10, &GpsRecorder::gpsCallback, this);

  std::string timestamp = getCurrentDateTime();
  nh.param<std::string>("/gps_recorder_node/folder_name_", folder_name_, "Day1/");

  const char* home_dir = std::getenv("HOME");
  if (home_dir == nullptr) {
    ROS_ERROR("Failed to get the home directory");
    return;
  }

  folder_loc_ = std::string(home_dir) + "/Documents/gps_data/";
  boost::filesystem::path dir(folder_loc_+folder_name_);
  if(boost::filesystem::create_directories(dir)) {
    ROS_INFO("Successfully created directories: %s", dir.c_str());
  }

  gps_file_.open((dir / ("gps_data_" + timestamp + ".csv")).string());
}

GpsRecorder::~GpsRecorder()
{
  gps_file_.close();
}


void GpsRecorder::gpsCallback(const sensor_msgs::NavSatFix::ConstPtr& msg)
{
  if (!gps_header_written_)
  {
    gps_file_ << "date_time,ros_time,gps_status,latitude,longitude,altitude" << std::endl;
    gps_header_written_ = true;
  }
  std::string dateTime = getCurrentDateTime();
  gps_file_ << dateTime << "," << ros::Time::now() << ","
  << msg->status.status<< ","
  << std::setprecision(14) << msg->latitude<< ","
  << std::setprecision(14) << msg->longitude << ","
  << msg->altitude << std::endl;
}

std::string GpsRecorder::getCurrentDateTime()
{
  auto now = std::chrono::system_clock::now();
  auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

  auto itt = std::chrono::system_clock::to_time_t(now);

  std::ostringstream ss;
  ss << std::put_time(std::localtime(&itt), "%m_%d_%Y_%H_%M_%S");
  ss << '_' << std::setw(3) << std::setfill('0') << milliseconds.count();

  return ss.str();
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "gps_recorder");
  ros::NodeHandle nh;

  GpsRecorder recorder(nh);

  ros::spin();

  return 0;
}
