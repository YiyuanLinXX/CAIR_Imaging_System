#pragma once

#include "singleCamera.h"

#include "Spinnaker.h"
#include <SpinGenApi/SpinnakerGenApi.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include <thread>
#include <mutex>
#include <chrono> 
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include <boost/circular_buffer.hpp>
#include <boost/algorithm/string.hpp>

#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>

//ros publish image
#include<image_transport/image_transport.h>
#include<cv_bridge/cv_bridge.h>


using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;

typedef std::chrono::time_point<std::chrono::system_clock> Stime;
namespace fs = boost::filesystem;

struct BFS_Params
{
    string triggerMode = "On";      // Use trigger to take images, if off, continuous taking
    string triggerSource = "Line0"; // Line0 Software

    string pixelFormat = "BayerRG8";
    
    string exposureAuto = "Off";
    string balanceWhiteAuto = "Off";//Off; Once
    string gainAuto = "Off";
    string triggerActivation = "FallingEdge";//RisingEdge

    float exposureTime = 400.0;      // Unit us
    float gain = 5.0;
    float balanceRatio = 1.2;
    
    // default settings:
    string acquisitionMode = "Continuous";  // Do Not Use "single frame". That means after start acquisition and take 1 picture, it will stop
    int acquisitionBurstFrameCount = 1;
    int triggerDelay = 14;  // in us
    
    
    bool acquisitionFrameRateEnable = true; // Auto set acquisition Frame Rate to 170hz, max 60 hz transfer
    float acquisitionFrameRate = 30;    // fps
};

struct ImagePac
{
    int image_id;

    string time_stamp;
    
    string time_stamp_ros;
    
    cv::Mat image;
    
    uint64_t timestamp;
    int64_t frameID;

};


class BFS_camera: public singleCamera
{
public:
    BFS_camera(){};
	BFS_camera(CameraPtr P_cam);
	~BFS_camera();

	int cam_connect();              // Connect to the camera

    int set_params(map<string, string> params); // Read camera parameters

	int cam_init();                 // Set parameters to camera, (re)start worker thread. 

	int set_shutter(float shutter);  
	int set_balanceWhiteAuto(string s);  
	int set_folder(string folder_name);
	
	int set_max_packet_size(int s);

    int cam_grab(cv::Mat& cv_img);       // After filling trigger, grab the image to a cv Mat, called by upper level/other class
	
    bool cam_trigger_ready();               // Check if the camera trigger is ready
	void cam_trigger(string& trigger_time, string& trigger_time_ros);  // Trigger the camera, depend on the triggering type, file software trigger or not. Enable the listenning thread to receive one frame.
	int cam_disconnect();

    int cam_get_img(cv::Mat& mat_out);

    // Camera parameters
	BFS_Params      camParas;

    // Camera control/connection related
	CameraPtr       pCam;           // The camera object pointer
    INodeMap*       pNodeMap;       // Parameters map
    INodeMap*       pDevNodeMap;    // Containing the serial number, for telling left or right

    // Working mode. Activate: Triggered by this module, save timestamps. Passive: Triggered by other modules, no need to save timestamps.
    bool    is_active_mode_ = true;
    
    string CurrentOutputFolder = "Images/";
    
    ofstream outFile;
    
    string  getCurrentDateStr();
    string  getCurrentTimeStr();
    struct  tm      *ptm;
    struct  timeb   stTimeb;
    static  char    szTime[30];
    
    int get_private_save_id();

	void set_private_save_id(int new_id);
	
	void initializeId();
	
	cv::Mat         publishImage0;
	cv::Mat         publishImage;
	
	bool if_preview = false;
	    
    
private:
    // Worker thread related
    // Worker thread entry function
    void    start_streaming();
    // Worker thread main function
    void    streaming();

    // Image saving thread related
    void    start_saving();
    void    saving();


    ImagePtr        pImage;           // The image type supported by Spinnaker, used by the worker thread

    // Sharing related
    cv::Mat         cvImage;         // The cv storage of the image, for sharing
    //std::deque<std::pair<int, cv::Mat>> img_buffer_;     // Buffer of the images to save, paired with ms timestamp

	std::deque<ImagePac> img_buffer_;
    // Node functions
    int set_node_val(INodeMap* p_node_map, string node_name, string value);
    int set_node_val(INodeMap* p_node_map, string node_name, int value);
    int set_node_val(INodeMap* p_node_map, string node_name, float value);
    int set_node_val(INodeMap* p_node_map, string node_name, bool value);
    template<typename T>
        int get_node_val(INodeMap* p_node_map, string node_name, T& value);

    int private_save_id = 0;

	string dataPath = "/home/cairlab/Data/";//   "/home/phenobot3/catkin_ws/Data/"
	string triggered_time;
	string triggered_time_ros;
};

int PrintCameraInfo(INodeMap & nodeMap);

typedef boost::shared_ptr<BFS_camera> ptrCamera;
typedef boost::circular_buffer<Stime> tsBuffer;


#include "jetsonGPIO.h"

class BFSMulti
{
public:
    BFSMulti();
    ~BFSMulti();

    // Connect a new camera to organize together, with its parameters
    void BFS_new(ptrCamera pcamera, std::map<string, string>& paras_cams);

    int BFSM_disconnect();

    // Syncronization
    void BFSM_sync(Stime ts);

    // Set parameters
    int BFSM_set_param(std::map<string, std::map<string, string>>& paras_cam, std::string save_path = "");

    // Set exposure (shutter)
    int BFSM_set_exposure(int t_us);
    int BFSM_set_balanceWhiteAuto(string s);
	
    int BFSM_set_maxPacketSize(int s);
    
    int BFSM_set_folder(string folder_name);

    // Start capturing
    int BFSM_start_capturing();

    // Trigger camera
    int BFSM_trigger(string& ts, string& ts_ros);

    // Auto trigger
   // int BFSM_auto_trigger(int frame, float freq = 12.0f);
    int BFSM_stop_trigger();

    // Get preview images
    int BFSM_get_previews(std::vector<cv::Mat>& vec_imgs);

    // All the cameras
    std::vector<boost::shared_ptr<BFS_camera>> cameras_;
    // Number of cameras
    int nCams_ = 0;
    // Current exposure(shutter), if < 0, not read
    int exposure_us_ = -1;
    // "Soft", "GPIO" or "Client", "Soft" needs to software trigger at least one camera. "GPIO": trigger all cameras through GPIO. "Client": cameras are all triggered by other modules/computers 
    string  moduleMode_ = "GPIO";
    //string  moduleMode_ = "Client";  

    bool    cont_triggering_ = false;   
    
    void initializeIds();
    
    string BFSM_getCurrentTimeStr();
    
    int common_save_id = 0;
    
    bool BFS_if_preview = false; 
    
    
    
private:
    tsBuffer ts_buffer_;

    // The worker thread for triggering cameras without blocking
    std::thread thread_trigger_;   
    
};
