## Prerequisite

- Username: cairlab
- System: Ubntu 20.04
- Opencv 3.4.3 (c++)
- ROS1
- ROS Bridger Server (sudo apt-get install ros-<distro>-rosbridge-server)
- Spinnaker SDK 2.6.0.157



## Usage

1. Launch the camera service

```bash
roslaunch phenobot_camera start_camera.launch
```

2. Set the correct ip address in `PhenobotWebInterface-multiCam.html` 

```html
  var ip = "10.48.29.143"; //set the ip address as it of the computer
```

3. Open `PhenobotWebInterface-multiCam.html` with Google Chrome Browser, and click `Camera` button on the life sidebar.
4. Refresh the browser, and if the connection is good, you will see output in the terminal as follow

```bash
Client connected.  1 clients total.
```

5. Choose camera(s) you need to connect by clicking `PhenoStereo1` and once you finish all the basic setting in the browser, click `connect` button in the web interface. If the connection is successful, the output will be like follow

```bash
*** CONFIGURING CHUNK DATA ***

Chunk mode activated...
Enabling entries...
	Image: enabled
	CRC: enabled
	FrameID: enabled
	OffsetX: enabled
	OffsetY: enabled
	Width: enabled
	Height: enabled
	ExposureTime: enabled
	Gain: enabled
	BlackLevel: enabled
	PixelFormat: enabled
	Timestamp: enabled
	SequencerSetActive: enabled
	SerialData: enabled
	ExposureEndLineStatusAll: enabled
camID: 0143EF86
connect to camera 0143EF86
Cameras connected: 1
```

8. Set the exposure time, gain, balance ratio, frame rate by entering in the web interface, and click `publish` to save to settings.
9. Set the folder name that you want to save your images in the web interface, otherwise the images captured will not be saved!
   :star: **Note**: there displays pre-filled content "row1" in the blank, but you still need to click `create_folder` to set the path to save images. The default folder doesn't exist and no images will be saved if you don't create a new folder. The data will be saved in `home/cairlab/Data/{folername_you_set}`
10. Click `start_capturing` to start the camera
11. Click `cont_trigger` to make the camera receive trigger signals from GPIO
12. Click `start_preview` to display the images captured in the web interface and save images in JPEG format
13. To stop functions in the web interface, click corresponding button with "stop"
14. Click `disconnect` to disconnect cameras before stopping the program or unplugging cameras



## Functions

- publish
  - change and publish the parameters setting such as exposure time, balance ratio
- connect
  - connect cameras
- create_folder
  - create the folder to save images captured
- start_capturing
  - start capturing images
- cont_trigger
  - start receiving continuous trigger signals from GPIO
- stop_cont_trigger
  - stop receiving continuous trigger signals from GPIO
- start_preview
  - display images in the web interface, and the images will be saved in JPEG format
- stop_preview
  - stop displaying images in the web interface, and the images will be saved in PGM format
- disconnect
  - disconnect cameras



## Timestamp.csv

```csv
1,2024-04-08-16-09-29-770,1712606969.770175,1,57956530512
2,2024-04-08-16-09-32-209,1712606972.209874,2,58541592320
3,2024-04-08-16-09-32-309,1712606972.309978,3,59126749112
4,2024-04-08-16-09-32-838,1712606972.838278,4,59711905808
```

- column 1: the frame ID of the saved image
- column 2: computer time (less accurate)
- column 3: ROS time stamp (less accurate)
- column 4: Chunk frame ID (the frame ID of the captured image)
- column 5: Chunk time (very accurate, in nanosecond level)



## Reference

[Synchronizing a Blackfly or Grasshopper3 GigE Camera’s Time to PC Time](https://www.flir.com/support-center/iis/machine-vision/application-note/synchronizing-a-blackfly-or-grasshopper3-gige-cameras-time-to-pc-time/)



