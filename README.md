# README

This repository includes the software for our imaging system. This is a general introduction without details about hardware configuration because the hardware settings are totally different among deployed locations. Please refer to the specific one for more detailed instruction.

The program passed all tests with ROS Noetic on Ubuntu 20.04.

**NOTE**: For the other ROS versions and Ubuntu versions, there is no guarantee that it can run with other ROS versions or OS.



## Prerequisite

We hardcoded the user name and folder path in the software, so you will need to set your user name as `cairlab`.

- Username: cairlab
- System: Ubntu 20.04

- Install [Spinnaker SDK](https://www.teledynevisionsolutions.com/support/support-center/software-firmware-downloads/iis/spinnaker-sdk-download/spinnaker-sdk--download-files/?pn=Spinnaker+SDK&vn=Spinnaker+SDK). If you are installing Spinnaker 2.6.0.160 (which is the version we used but not listed on the official website), you can also check the installation files for Ubuntu 20.04 in the folder `/spinnaker-2.6.0.160-amd64`.

- Install [OpenCV 3.4.3](https://docs.opencv.org/3.4.3/) for C++.

- Install packages for your ROS distro by running:

  ```bash
  sudo apt-get install ros-<distro>-serial ros-<distro>-rosbridge-server qt5-default qtcreator
  ```

  We use ROS 1 Noetic, so we put the following command to install all the needed packages.
  ```bash
  sudo apt-get install ros-noetic-serial ros-noetic-rosbridge-server qt5-default qtcreator
  ```

- Install packages for Python by running:
  ```bash
  pip3 install pillow numpy opencv-python tqdm argparse pandas matplotlib
  ```

  

## Usage

0. Make sure all the hardware connection are correct, ensure the status of RTK correction and GPS coordinates is FIX.

1. Double-click to run the executable file `start_gps.sh` or run it in the terminal. Select the port and baud rate for your GPS receiver, then press `Start GPS` and wait for a while until it display "GPS Ready". Then enter the folder name you want to save the raw GPS data in the blank after "Start Recording". The raw data of GPS will be saved in `Documents/gps_data/{folder_name_you_set}`.
1. Open a terminal (press `CTRL+ALT+T`, and launch the camera service

```bash
roslaunch phenobot_camera start_camera.launch
```

3. Set the IP address as the localhost "127.0.0.1" or the correct IP address of your device in `PhenobotWebInterface-multiCam.html` 

```html
  var ip = "127.0.0.1"; // or set the ip address as it of the computer
```

4. Open `PhenobotWebInterface-multiCam.html` with Google Chrome Browser, and click `Camera` button on the life sidebar. Refresh the browser, and if the connection is good, you will see output in the terminal as follow

```bash
Client connected.  1 clients total.
```

5. Check `PhenoStereo1` and then click `connect` button in the web interface. If the connection is successful, the output will be like follow:

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
connect to camera 0143EF87
Cameras connected: 2
```

6. Set the folder name (**==SAME== as the one you use for the GPS data**, for convenience) in the blank of "FolderName" in the web interface to save your images, otherwise the images captured will **NOT** be saved! The data will be saved in `home/cairlab/Data/{folder_name_you_set}`

   **Note**: there displays pre-filled content "row1" in the blank, but you still need to click `create_folder` to set the path to save images. The default folder doesn't exist and no images will be saved if you don't create a new folder.

7. Set the exposure time, gain, balance ratio, frame rate by entering in the web interface, and click `publish` to save to settings.

8. Click `start_capturing` in the web interface to start the camera, then click `cont_trigger` in the web interface to trigger the camera through GPIO.

9. (Optional) Click `start_preview` to display the images captured in the web interface and save images in JPEG format.

   **NOTE**: To stop functions in the web interface, click corresponding button with "stop".

10. After data collection, click `stop_cont_trigger` first, and then click `disconnect` to disconnect the camera(s) and stop the image data collection. Now you can close the web interface. Close all the terminals and windows. Check the data collected in folder `Data` and folder `gps_data`. 



## Functions and Buttons in Web Interface

- `publish`
  - change and publish the parameters setting such as exposure time, balance ratio
- `connect`
  - connect cameras
- `create_folder`
  - create the folder to save images captured
- `start_capturing`
  - start capturing images
- `cont_trigger`
  - start receiving continuous trigger signals from GPIO
- `stop_cont_trigger`
  - stop receiving continuous trigger signals from GPIO
- `start_preview`
  - display images in the web interface, and the images will be saved in JPEG format
- `stop_preview`
  - stop displaying images in the web interface, and the images will be saved in PGM format
- `disconnect`
  - disconnect cameras



## Timestamp.csv

| Frame ID | Computer Time           | ROS Time Stamp | Chunk Frame ID | Chunk Time  | Latitude | Longitude |
| -------- | ----------------------- | -------------- | -------------- | ----------- | -------- | --------- |
| 1        | 2024-09-27-15-48-36-040 | 1727466516     | 9737           | 6.25821E+12 | 42.8786  | -77.0167  |
| 2        | 2024-09-27-15-48-36-290 | 1727466516     | 9738           | 6.25873E+12 | 42.8786  | -77.0167  |
| 3        | 2024-09-27-15-48-37-855 | 1727466518     | 9739           | 6.25926E+12 | 42.8786  | -77.0167  |
| 4        | 2024-09-27-15-48-38-374 | 1727466518     | 9740           | 6.25978E+12 | 42.8786  | -77.0167  |
| ...      | ...                     | ...            | ...            | ...         | ...      |           |

- Frame ID: ID of the **saved** images
- Computer time: less accurate time stamp
- ROS time stamp:  less accurate time stamp
- Chunk frame ID : ID of the **captured** images (may not be saved)
- Chunk time: very accurate time stamp, in nanosecond (ns) level
- Latitude: GPS coordinate
- Longitude: GPS coordinate



## Reference

[Synchronizing a Blackfly or Grasshopper3 GigE Camera’s Time to PC Time](https://www.flir.com/support-center/iis/machine-vision/application-note/synchronizing-a-blackfly-or-grasshopper3-gige-cameras-time-to-pc-time/)



