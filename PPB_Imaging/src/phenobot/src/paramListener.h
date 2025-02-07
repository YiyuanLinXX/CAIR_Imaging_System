#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include <string>
#include <map>
#include <iostream>
#include "flirBFS.h"
#include <json/json.h>
//#include <jsoncpp/json/json.h>
#include <json/value.h>

#include <chrono>  // chrono::system_clock
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time
#include <fstream>
#include <iostream>

//ros publish image
#include<image_transport/image_transport.h>
#include<cv_bridge/cv_bridge.h>

using namespace std;

class Param_listener: public BFSMulti
{

public:
    Param_listener(ros::NodeHandle* nodehandle); 

    ~Param_listener();
    
    std::map<string, string> params_rev;

	SystemPtr system;

	CameraList camList;
	
	std::map<string, std::map<string, string>> paras_cams;

	boost::shared_ptr<BFSMulti> pCameras{new BFSMulti()}; 
	
	std::thread _threadWorker;

    ros::Time ros_time; 
	double rostimeSec;
	
	string str;
	
	ofstream myfile;
private:

    ros::NodeHandle nh_;
    ros::NodeHandle nhi_;

	ros::Subscriber connect_sub;
	
    ros::Subscriber cont_trigger_sub;
	ros::Subscriber stop_cont_trigger_sub;
    ros::Subscriber disconnect_sub;
    ros::Subscriber frame_rate_sub;
	ros::Subscriber capture_sub;
	ros::Subscriber exposureTime_sub;
	ros::Subscriber folderName_sub;
	ros::Subscriber balanceWhiteAuto_sub;
    ros::Subscriber start_preview_sub;
    ros::Subscriber stop_preview_sub;

    void createDayFolder();

    string CurrentDayFolder;
    
    string CurrentRowFolder;

    string getCurrentDateStr();

	void initParamMap(); 
	void listen_param();
	void connectCallback(const std_msgs::String::ConstPtr& msg);
	void stopContTriggerCallback(const std_msgs::String::ConstPtr& msg);
	void contTriggerCallback(const std_msgs::String::ConstPtr& msg);
	void disconnectCallback(const std_msgs::String::ConstPtr& msg);
	void frameRateCallback(const std_msgs::String::ConstPtr& msg);
	void folderNameCallback(const std_msgs::String::ConstPtr& msg);
	void captureCallback(const std_msgs::String::ConstPtr& msg);
	void exposureTimeCallback(const std_msgs::String::ConstPtr& msg);
	void balanceWhiteAutoCallback(const std_msgs::String::ConstPtr& msg);
	void startPreviewCallback(const std_msgs::String::ConstPtr& msg);
    void stopPreviewCallback(const std_msgs::String::ConstPtr& msg);
	void preview();
	void preciseSleep(double seconds);

	string dataPath = "/home/cairlab/Data/"; // "/home/phenobot3/catkin_ws/Data/"   /home/nvidia/catkin_ws/Data/

	bool systemCreated = false;
	
	image_transport::Publisher pub, pub1, pub2, pub3, pub4, pub5, pub6, pub7, pub8, pub9, pub10;
    std::vector<image_transport::Publisher> pubvector;
    
    int cam_count;
    
    double frame_rate=10.f;

	int sleep_time=100;
};
