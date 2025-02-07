#include "flirBFS.h"
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include <json/json.h>

#include <map>
#include <gtest/gtest.h>

#include <b64/encode.h>
#include <b64/decode.h>

#include "socketServer.h"


using namespace std;

// Serialize a cv::Mat to a stringstream
stringstream serialize(cv::Mat input)
{
    size_t size = input.total() * input.elemSize();

    stringstream ss;

    // Write the whole image data
    ss.write((char*)input.data, size);

    return ss;
}

// Function to compose the preview messages
void composePreviewMsg(Json::Value& js_root, std::vector<cv::Mat>& vec_imgs)
{
    
    js_root["n_imgs"] = int(vec_imgs.size());
    js_root["imgs"] = Json::arrayValue;
    base64::encoder enc;
    for(cv::Mat img : vec_imgs)
    {
        // Serialize the input image to a stringstream
        Json::Value img_json;
        img_json["width"] = int(img.cols);
        img_json["height"] = int(img.rows);
        img_json["type"] = int(img.type());
        img_json["size"] = int(img.total() * img.elemSize());
        stringstream serializedStream = serialize(img);
        stringstream encoded;
        enc.encode(serializedStream, encoded);
        img_json["data"] = encoded.str();

        js_root["imgs"].append(img_json);
    }
    
}

std::chrono::system_clock::time_point string_to_time_point(const std::string &str)
{
    using namespace std;
    using namespace std::chrono;

    int yyyy, mm, dd, HH, MM, SS, fff;

    char scanf_format[] = "%4d.%2d.%2d-%2d.%2d.%2d.%3d";

    sscanf(str.c_str(), scanf_format, &yyyy, &mm, &dd, &HH, &MM, &SS, &fff);

    tm ttm = tm();
    ttm.tm_year = yyyy - 1900; // Year since 1900
    ttm.tm_mon = mm - 1; // Month since January 
    ttm.tm_mday = dd; // Day of the month [1-31]
    ttm.tm_hour = HH; // Hour of the day [00-23]
    ttm.tm_min = MM;
    ttm.tm_sec = SS;

    time_t ttime_t = mktime(&ttm);

    system_clock::time_point time_point_result = std::chrono::system_clock::from_time_t(ttime_t);

    time_point_result += std::chrono::milliseconds(fff);
    return time_point_result;
}

std::string time_point_to_string(std::chrono::system_clock::time_point &tp)
{
    using namespace std;
    using namespace std::chrono;

    auto ttime_t = system_clock::to_time_t(tp);
    auto tp_sec = system_clock::from_time_t(ttime_t);
    milliseconds ms = duration_cast<milliseconds>(tp - tp_sec);

    std::tm * ttm = localtime(&ttime_t);

    char date_time_format[] = "%Y.%m.%d-%H.%M.%S";

    char time_str[] = "yyyy.mm.dd-HH.MM.SS.fff";

    strftime(time_str, strlen(time_str), date_time_format, ttm);

    string result(time_str);
    result.append(".");
    result.append(to_string(ms.count()));

    return result;
}

TEST(DISABLED_StereoTest, NoSocketTest)
{
    //******** Configure cameras *******//
    boost::shared_ptr<BFSMulti> pCameras(new BFSMulti()); 

    // Map of map to store the parameters
    std::map<string, std::map<string, string>> paras_cams;

    //******** Read json settings *******//
    std::ifstream config_doc("config.json");
    Json::Value config;
    config_doc >> config;

    // Save path
    fs::path base_save_path(config["base_save_path"].asString());

    // Check working mode            
    pCameras->moduleMode_ = config["module_mode"].asString();

    for( int index = 0; index < config["cameras"].size(); index++ ) 
    {
        std::map<string, string> param;
        param["ExposureTime"] = config["cameras"][index]["ExposureTime"].asString();
        if (pCameras->moduleMode_ == "Soft")
            param["TriggerSource"] = config["cameras"][index]["TriggerSource"].asString();
        else
            param["TriggerSource"] = "Line0";
        paras_cams[config["cameras"][index]["serial"].asString()] = param;
    }

    //ASSERT_EQ(config["cameras"].size(), 2);

    // Retrieve reference to system object
    SystemPtr system = System::GetInstance();
    // Retrieve list of cameras from the system
    CameraList camList = system->GetCameras();

    unsigned int numCameras = camList.GetSize();

    cout << "Number of cameras detected: " << numCameras << endl << endl;

    // Finish if there are no cameras
    if (numCameras == 0)
    {
        // Clear camera list before releasing system
        camList.Clear();

        // Release system
        system->ReleaseInstance();

        cout << "Not enough cameras!" << endl;

        return;
    }

    std::vector<boost::shared_ptr<BFS_camera>> cameras;

    // Init, connect to cameras
    for(int id = 0; id < numCameras; id++)
    {
        CameraPtr pCam = camList.GetByIndex(id);
    
        // Test the BFS camera class
        boost::shared_ptr<BFS_camera> pCamera(new BFS_camera(pCam));
        pCamera->cam_connect();

        // Get camera ID, check valid
        string camID = pCamera->cameraID;

        // Set parameters
        if(paras_cams.find(camID) != paras_cams.end())
            pCameras->BFS_new(pCamera, paras_cams[camID]);
        else{
            pCamera->cam_disconnect();
            continue;
        }
    }
    
    std::cout<<"Cameras connected: " << pCameras->nCams_ <<std::endl;
    //ASSERT_EQ(pCameras->nCams_, 2);

    // ** Camera control ** //
    Stime ts_sync = std::chrono::system_clock::now();

    // Sync
    pCameras->BFSM_sync(ts_sync);

    // Set parameters
    pCameras->BFSM_set_param(paras_cams);

    
    // Start capturing
    pCameras->BFSM_start_capturing();


    // Camera trigger

    int ttt = 0;

    std::vector<Stime> vec_ts(10);

    for(int i = 0; i < 10; i++)
    {
        int r_tg = pCameras->BFSM_trigger(vec_ts[i]);
        if(r_tg==0)
            std::cout<<"Trigger"<<std::endl;
        else
        {
            std::cout<<"Trigger failed"<< std::endl;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    pCameras->BFSM_disconnect();

    camList.Clear();

    system->ReleaseInstance();  // Will report error here

    std::cout<<"Program end"<<std::endl; 
}

//typedef std::deque<std::string> msg_queue;

TEST(StereoTest, SocketTest)
{
    // Used by cameras
    std::map<string, std::map<string, string>> paras_cams;
    boost::shared_ptr<BFSMulti> pCameras(new BFSMulti()); 
    std::vector<boost::shared_ptr<BFS_camera>> cameras;
    // Retrieve reference to system object
    SystemPtr system = System::GetInstance();
    // Retrieve list of cameras from the system
    CameraList camList = system->GetCameras();
    // Store timestamp for single shot
    Stime ts;

    // Stime to send preview to the host
    Stime ts_preview;    
    //bool preview_required = false;
    std::vector<cv::Mat> img_preview_vec;
    // The time interval to last preview. If negtive, disable preview. If zero, preview once.
    int ms_preview_interval = -1; 
    
    // Server
    msg_queue send, recv;
    boost::asio::io_service io_service;
    server socket_worker(io_service, 2018);
    socket_worker.run(recv, send);
    boost::mutex mutex;

    // Response message composer
    Json::FastWriter fastwriter;

    std::cout<<"socket_worker started"<<std::endl;
    // Main loop
    while(1)
    {
        // No new command to process, process previews
        if(recv.empty())
        {
            int ms_delta_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - ts_preview).count();
        
            // Preview messages
            if(ms_preview_interval >= 0 && 
                ms_delta_time > ms_preview_interval &&
                (pCameras->BFSM_get_previews(img_preview_vec) == 0)){
                
                Json::Value res_root;
                res_root["command"] = "images";
                
                composePreviewMsg(res_root, img_preview_vec);

                std::string res_msg = fastwriter.write(res_root);
                send.push_back(res_msg);
                
                // reset preview timer
                ts_preview = std::chrono::system_clock::now();
            }
            else
                std::this_thread::sleep_for(std::chrono::milliseconds(10));

            if(ms_preview_interval == 0 || !pCameras->cont_triggering_) 
                ms_preview_interval = -1;
            
            continue;
        }

        mutex.lock();
        std::string msg_str = recv.front();
        std::cout<<"[Recv]:"<<msg_str<<std::endl;
        //std::cout<<"Recv buffer size: "<<recv.size()<<std::endl;
        recv.pop_front();
        //std::cout<<"Recv buffer size after pop: "<<recv.size()<<std::endl;
        mutex.unlock();

        // Decode message
        Json::Value msg_recv;
        Json::Reader json_decoder;
        bool b_parse = json_decoder.parse(msg_str.c_str(), msg_recv);   
 
#if 1
        if(!b_parse)    // Failed
        {
            std::cout << "Not able to parse the message, message is:"<<std::endl;
            std::cout<<msg_str<<std::endl;
            continue;
        }
        

        ///********** Parse message command ******************//

        if (msg_recv["command"].asString() == "connect"){

            // Initialize response message
            Json::Value res_root;
            res_root["command"] = "connect";

            //******** Configure cameras *******//
            std::ifstream config_doc("config.json");
            Json::Value config;
            config_doc >> config;

            // Reset the cameras
            pCameras->BFSM_disconnect();
            // Retrieve reference to system object
            system = System::GetInstance();
            // Retrieve list of cameras from the system
            camList = system->GetCameras();

            // Save path
            fs::path base_save_path(config["base_save_path"].asString());

            // Check working mode            
            pCameras->moduleMode_ = config["module_mode"].asString();

            std::cout<<"Module working mode: " << pCameras->moduleMode_ << std::endl;

            for( int index = 0; index < config["cameras"].size(); index++ ) 
            {
                std::map<string, string> param;
                param["ExposureTime"] = config["cameras"][index]["ExposureTime"].asString();
                if (pCameras->moduleMode_ == "Soft")
                    param["TriggerSource"] = config["cameras"][index]["TriggerSource"].asString();
                else
                    param["TriggerSource"] = "Line0";

                paras_cams[config["cameras"][index]["serial"].asString()] = param;
            }

            unsigned int numCameras = camList.GetSize();

            cout << "Number of cameras detected: " << numCameras << endl << endl;
            
            // Finish if there are no cameras
            if (numCameras == 0)
            {
                // Clear camera list before releasing system
                camList.Clear();

                // Release system
                system->ReleaseInstance();

                cout << "No enough cameras!" << endl;
                res_root["data"] = "No enough cameras!";
                std::string res_msg = fastwriter.write(res_root);
                recv.push_back(res_msg);
                break;
            }

            // Init, connect to cameras
            for(int id = 0; id < numCameras; id++)
            {
                CameraPtr pCam = camList.GetByIndex(id);
            
                // Test the BFS camera class
                boost::shared_ptr<BFS_camera> pCamera(new BFS_camera(pCam));
                pCamera->cam_connect();

                // Get camera ID, check valid
                string camID = pCamera->cameraID;

                // Set parameters
                if(paras_cams.find(camID) != paras_cams.end())
                    pCameras->BFS_new(pCamera, paras_cams[camID]);
                else{
                    pCamera->cam_disconnect();
                    continue;
                }
            }
            std::cout<<"Cameras connected: " << pCameras->nCams_ <<std::endl;
            res_root["data"] = "OK, Cameras connected: "+std::to_string(pCameras->nCams_);

            std::string res_msg = fastwriter.write(res_root);
            send.push_back(res_msg);
        }

        // ** Camera control ** //
        // Sync
        if (msg_recv["command"].asString() == "sync"){
            // Local system time when received this
            Stime ts_sync = std::chrono::system_clock::now();
            // The time reference from the host computer
            Stime ref_time = string_to_time_point(msg_recv["data"].asString());

            // Initialize response message
            Json::Value res_root;
            res_root["command"] = "sync";
            res_root["data"] = "OK";

            pCameras->BFSM_sync(ts_sync);

            std::string res_msg = fastwriter.write(res_root);
            send.push_back(res_msg);
        }

        // Set parameters
        if (msg_recv["command"].asString() == "set_paras"){
            // Initialize response message
            Json::Value res_root;
            res_root["command"] = "set_paras";

            // New parameters
            if(msg_recv["data"] != "")
            {
                std::cout<<"Set param not implemented"<<std::endl;
            }
            int res = pCameras->BFSM_set_param(paras_cams);

            if(res!=0)
                res_root["data"] = std::to_string(-res) + ", set para failed";
            else
                res_root["data"] = "OK";

            std::string res_msg = fastwriter.write(res_root);
            send.push_back(res_msg);
        }

        // Set shutter
        if (msg_recv["command"].asString() == "set_exposure"){
            std::cout<<"[Main] set_exposure"<<std::endl;
            // Initialize response message
            Json::Value res_root;
            res_root["command"] = "set_exposure";

            float exposure = msg_recv["data"].asFloat();

            int res = pCameras->BFSM_set_exposure(exposure);

            if(res!=0)
                res_root["data"] = std::to_string(-res) + ", set para failed";
            else
                res_root["data"] = "OK";

            std::string res_msg = fastwriter.write(res_root);
            send.push_back(res_msg);
        }

        // Start capturing
        if (msg_recv["command"].asString() == "start_capturing"){
            // Initialize response message
            Json::Value res_root;
            res_root["command"] = "start_capturing";

            int res = pCameras->BFSM_start_capturing();
            if(res!=0)
                res_root["data"] = std::to_string(-res) + ", start capturing failed";
            else
                res_root["data"] = "OK";

            std::string res_msg = fastwriter.write(res_root);
            send.push_back(res_msg);
        }

        // Single trigger
        if (msg_recv["command"].asString() == "single_trigger"){
            // Initialize response message
            Json::Value res_root;
            res_root["command"] = "single_trigger";

            int r_tg = pCameras->BFSM_trigger(ts);

            if(r_tg!=0)
                res_root["data"] = "Trigger time out";
            else
                res_root["data"] = "OK";

            std::string res_msg = fastwriter.write(res_root);
            send.push_back(res_msg);

            // Block the thread to wait for the preview image ready
            std::this_thread::sleep_for(std::chrono::milliseconds(50));

            // Enable preview once
            ms_preview_interval = 0;
        }
        
        // Continuous trigger
        if (msg_recv["command"].asString() == "cont_trigger"){
            // Initialize response message
            Json::Value res_root;
            res_root["command"] = "cont_trigger";

            int frames = stoi(msg_recv["data"].asString());
            int res = pCameras->BFSM_auto_trigger(frames);

            // For preview
            ts_preview = std::chrono::system_clock::now();

            if(res!=0)
                res_root["data"] = "cont_trigger time out";
            else
                res_root["data"] = "OK";

            std::string res_msg = fastwriter.write(res_root);
            send.push_back(res_msg);

            // Enable continuous preview
            ms_preview_interval = 200;
        }

        // Stop trigger
        if (msg_recv["command"].asString() == "stop_trigger"){
            // Initialize response message
            Json::Value res_root;
            res_root["command"] = "stop_trigger";

            int res = pCameras->BFSM_stop_trigger();

            if(res!=0)
                res_root["data"] = "Stop_trigger failed";
            else
                res_root["data"] = "OK";

            std::string res_msg = fastwriter.write(res_root);
            send.push_back(res_msg);
        }

        // Disconnect
        if (msg_recv["command"].asString() == "disconnect"){
            // Initialize response message
            Json::Value res_root;
            res_root["command"] = "disconnect";
            int res = pCameras->BFSM_disconnect();

            if(res!=0)
                res_root["data"] = "disconnect time out";
            else
                res_root["data"] = "OK";

            std::string res_msg = fastwriter.write(res_root);
            send.push_back(res_msg);
        }
#endif
    }

    camList.Clear();

    system->ReleaseInstance();  // Will report error here

    std::cout<<"Program end"<<std::endl; 
}

// Test pulse output with background thread
// Measure maximum frequency. 
TEST(DISABLED_StereoTest, GPIOTest)
{
    using namespace std;
    bool running = true;
    std::thread thread_worker([&running]()
        {
            cout<<"Thread start"<<endl;
            Stime t_start = std::chrono::system_clock::now();
            int n_pulse = 0;
            gpioExport(gpio397);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            gpioSetDirection(gpio397, outputPin);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            cout<<"Pulse start"<<std::endl;
            for(int i = 0; i < 1e4; i++)
            {
                gpioSetValue(gpio397, on);
                //std::this_thread::sleep_for(std::chrono::microseconds(10));
                gpioSetValue(gpio397, off);
                //std::this_thread::sleep_for(std::chrono::microseconds(10));
                n_pulse++;
                if(n_pulse >= 1e3)
                {
                    int us_dif = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - t_start).count();
                    cout<<"Fequency: "<<1.0e6*1e3/us_dif<<" hz"<<endl;
                    t_start = std::chrono::system_clock::now();
                    n_pulse = 0;
                }
            }

            gpioUnexport(gpio397);
            cout<<"Thread end"<<endl;
            running = false;
            return;
        }
    );

    //while(running)
    //{
    //    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        //std::cout<<"."<<std::endl;
    //}
    thread_worker.join();
    cout<<"Ended"<<endl;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
