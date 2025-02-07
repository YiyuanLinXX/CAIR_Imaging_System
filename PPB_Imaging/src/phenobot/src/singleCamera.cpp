
// A template for one single camera. Each camera has a worker thread to listen to recieved images.
// Also, each camera has function of connect, init, setParam, getImage, and auto_saving functions

#include "singleCamera.h"

void sensorSyncNSave::set_save_path(std::string path)
{
    std::cout<<"["<<cameraID<<"]";
    if(csv_writter.is_open())
        csv_writter.close();
    fs::path fspath(path);  // base folder
    if(path=="")
        fspath = fs::current_path();

    save_id = 0;
    // Create the folder, first the base folder
    fs::create_directories(fspath);
    // Then the camera ID folder
    fs::create_directory(fspath/fs::path(cameraID));

    // The subfolder named with time (mmddHHMMSS)
    Stime now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_c);
    char buff[16];
    strftime(buff, sizeof(buff), "%m%d%H%M%S", &now_tm);
    std::string time_str = std::string(buff);

    fs::create_directory(fspath/fs::path(cameraID)/fs::path(time_str));

    // Fail to create the folder
    if(!fs::exists(fs::path(path)/fs::path(cameraID)))   {
        std::cerr<<"Fail to create dir under:"<<fspath.string()<<std::endl;
        // Make folder under current path
        fspath = fs::current_path();
        fs::create_directory(fspath/fs::path(cameraID));
        fs::create_directory(fspath/fs::path(cameraID)/fs::path(time_str));
    }

    save_path = (fspath/fs::path(cameraID)/fs::path(time_str)).string();

    std::cout<<"Save dir:"<<save_path<<std::endl;   

    // Open the file logger, write header 
    fs::path log_path = fs::path(fspath)/fs::path(time_str + "_" + cameraID + ".csv");
    csv_writter.open(log_path.string());

    if(fields.size()==0)
        fields.push_back("filename");

    if(csv_writter.is_open()){
        csv_writter<<"timestamp";
        for(string s:fields) csv_writter<<","<<s;
        csv_writter<<std::endl;
    }
    else
        std::cerr<<"Could not open camera logger "<<log_path.string()<<std::endl;
}

void sensorSyncNSave::write_data(Stime src, std::vector<string>& data)
{
    if(csv_writter.is_open()){
        csv_writter<<calc_stime_ms_diff(src);
        for(string s:fields) 
            csv_writter<<","<<s;
        csv_writter<<std::endl;
    }
}

void singleCamera::setup_sync(Stime ref)
{
    _syncSave.set_sync_clock(ref);
}

void singleCamera::setup_save(bool auto_save, string camera_id, string path, vector<string> fields)
{
    autoSave = auto_save;
    cameraID = camera_id;
    _syncSave.cameraID = camera_id;
    _syncSave.save_id = 0;
    if(auto_save)
    {
        _syncSave.set_fields(fields);
        _syncSave.set_save_path(path);
    }
}
