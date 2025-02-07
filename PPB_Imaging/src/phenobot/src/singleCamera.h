#pragma once

// A template for one single camera. Each camera has a worker thread to listen to recieved images.
// Also, each camera has function of connect, init, setParam, getImage, and auto_saving functions

#include <string>
#include <map>
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>

typedef std::chrono::time_point<std::chrono::system_clock> Stime;
namespace fs = boost::filesystem;
using namespace std;

// A class handeling sensor syncronization and saving the timestamps to a csv file,
// Not require both to work simutaniously
class sensorSyncNSave
{
public:
    sensorSyncNSave(){}
    ~sensorSyncNSave(){
        if(csv_writter.is_open())
            csv_writter.close();
    }

    // The refence clock, as timestamp 0
    void        set_sync_clock(Stime ref){ref_clock = ref;} 
    // Set the path and filename of the record file
    void        set_save_path(std::string path);  
    // Set the time difference between the reference, as timestamp  
    uint32_t    calc_stime_ms_diff(Stime src)   
        {return std::chrono::duration_cast<std::chrono::milliseconds>(src-ref_clock).count();}      
    // Set the fields    
    void        set_fields(std::vector<string> vec_fds){ fields = vec_fds; }        
    // Write data to file
    void        write_data(Stime src, std::vector<string>& data);

    std::string     save_path;      // The dir to save the timestamp files. 
    Stime           ref_clock;      // For calculating a syncronized time stamp
    std::ofstream   csv_writter;    // Saving timestamps and filenames  

    int save_id = 0;                // Data id for saving

    std::vector<std::string> fields;    // OTHER THAN timestamps

    std::string cameraID;           // The unique camera ID, as the folder name, csv file name
};

// A general pattern for a single camera
class singleCamera
{
public:
    singleCamera(){
    ptsTrigger = new std::string;
    ptsTriggerros = new std::string;
    }
    ~singleCamera(){}

    bool    isConnected = false;  // Camera connection indicator
    bool    autoSave = false;     // Automaticly save the image upon received?

    std::string     cameraID;      // The identifier of the camera, serial number
    
    virtual int     cam_connect() = 0;      // Establish connection
    virtual int     cam_init() = 0;         // (Re) Init the camera, apply parameters

    virtual int     set_params(map<string, string> params) = 0; // Set a bunch of parameters
    // Called by upper level. 
    // 1. If software trigger, fire trigger, wake worker
    // 2. If I/O external trigger, wake worker
    // 3. If Streaming mode, do nothing
    virtual void     cam_trigger(string& trigger_time, string& trigger_time_ros) = 0;        
    
    virtual int     cam_disconnect() = 0;

    void            setup_sync(Stime ref);
    void            setup_save(bool auto_save, string cameraID, string path = "", vector<string> fields = vector<string>());

    int     imgId;                 // In-class counter, restart when begin streaming

protected:


    // Worker thread related
    // Worker thread entry function
    virtual void    start_streaming() = 0;
    // Worker thread main function
    virtual void    streaming() = 0;
    // Worker is working? Need to stop?
    bool        _streaming = false;

    // The listener/worker thread to pull images and save them
    std::thread _threadWorker;   
    // Mutex to prevent race while sharing image with other processes
    std::mutex  _updateMutex;  

    // Sync and save
    sensorSyncNSave _syncSave;
    // The timestampe of the most recent trigger
    string*       ptsTrigger;
    string*       ptsTriggerros;

    // Image saving thread related
    virtual void    start_saving() = 0;
    virtual void    saving() = 0;
    bool            is_saving_ = false;
    std::thread     thread_saver_;

    // Is triggering command filed? If it is continuous mode, keep true;
    bool            isTriggered = false;
};
