############################## ROS #################################
run ros:
roscore

run rosbridge server:
roslaunch rosbridge_server rosbridge_websocket.launch
rosrun mjpeg_server mjpeg_server

build project:
catkin_make

run the target:
rosrun phenobot main 

master_URI:
bash file: 
export ROS_MASTER_URI=http://192.168.0.196:11311/
export ROS_IP=192.168.0.198

run one roscore 

two cameras use the same ip address (hub)
############## about sync ####################
1. in host system: sudo apt install chrony
2. use servers from the NTP Pool Project: 
sudo gedit /etc/chrony/chrony.conf
add: pool 0.ubuntu.pool.ntp.org iburst to the conf file and restart
3. restart: sudo systemctl restart chrony.service
4. sudo systemctl status chrony.service

client:
1. open file: sudo gedit /etc/systemd/timesyncd.conf 
2. add NTP = [host ip address] 
example: NTP = 192.168.0.196
3. systemctl start systemd-timesyncd
4. systemctl status systemd-timesyncd
to change system time manually:  systemctl stop systemd-timesyncd

change system by command line: sudu date +%T -s "1:11:15"
get time by command line: date

camera opration:
1. connect: connect all the cameras
2. publish: update and set the parameters, only teh changed parameters will be set
3. start_capturing: let the cameras start streaming
4. disconnect: disconnect all the cameras

if software trigger: (hardware the same, we don't need the button hardware_trigger so far)
connect,
publish,
start_capturing: will wait for trigger
trigger: click trigger once, save one image

preview:
connect, publish, start_capturing, preview
when preview, only connenct one camera

################### camera configuration ####################
cd /home/nvidia/catkin_ws/src/phenobot
source camera_config.sh


camera checking list
file:///home/nvidia/Downloads/ArenaSDK_v0.1.4_Linux_ARM64/ArenaSDK_Linux_ARM64/docs/html/arena_sdk_linux.html

Jetson TX2 GPIO:
https://www.jetsonhacks.com/nvidia-jetson-tx2-j21-header-pinout/

camera specifications:
file:///home/nvidia/Downloads/PHX050S-Polarized_1.12.0.0_Documentation_English/html/camera_specification.html
red: power
black: GND
GREEN : LINE 0
BLUE: GPIO gnd
    

about document:
GPIO hardware trigger:
file:///home/nvidia/Downloads/PHX032S_1.5.0.0_Documentation_English/html/digital_io_setup_input.html

to get permission
 
sudo chmod a+x /home/nvidia/Downloads/dqn-tx1-for-nintendo-master/gpio/non_root/setup_gpio.sh

https://jkjung-avt.github.io/gpio-non-root/

* about camera IP address:

cd /home/nvidia/Downloads/ArenaSDK_v0.1.4_Linux_ARM64/ArenaSDK_Linux_ARM64/precompiledExamples

./IpConfigUtility /list

to force ip:

./IpConfigUtility /force -i 0 -a 192.167.1.41 -s 255.255.255.0 -g 0.0.0.0
sudo ifconfig eth1 192.167.1.1 netmask 255.255.255.0

./IpConfigUtility /force -i 0 -a 192.167.2.41 -s 255.255.255.0 -g 0.0.0.0
sudo ifconfig eth2 192.167.2.1 netmask 255.255.255.0

$ sudo sh -c "echo 'net.core.rmem_default=2097152' >> /etc/sysctl.conf"
$ sudo sh -c "echo 'net.core.rmem_max=2097152' >> /etc/sysctl.conf"
$ sudo sysctl -p


################## failed cases ###########

no camera connected:
check camera configuration:
cd /home/nvidia/catkin_ws/src/phenobot
source camera_config.sh

unable to open device:
restart
unable to get buffer data:
restart

###############GPIO
echo 388 > /sys/class/gpio/export
echo  out > /sys/class/gpio/gpio388/direction
echo 1 > /sys/class/gpio/gpio388/value


#

#apt-get update && #apt-get upgrade
gedit ~/.bashrc
add source devel/setup.bash at the last line
source ~/.bashrc
roslaunch phenobot_camera start_camera.launch


vim press i, switch to insert mode
Esc, :w, to save
:q to exit

List Scheduled Cron Jobs
# sudo crontab -l
no crontab for tecmint

https://www.tecmint.com/11-cron-scheduling-task-examples-in-linux/

echo$PATH
sudo mv camera_config.sh /etc/init.d

sudo chmod +x /etc/init.d/camera_config.sh
sudo chown root:root /etc/init.d/camera_config.sh
sudo update-rc.d camera_config.sh defaults
sudo update-rc.d camera_config.sh enable

https://askubuntu.com/questions/335242/how-to-install-an-init-d-script
https://smallbusiness.chron.com/run-command-startup-linux-27796.html
https://www.tecmint.com/auto-execute-linux-scripts-during-reboot-or-startup/
https://askubuntu.com/questions/228304/how-do-i-run-a-script-at-start-up

to remote access jetson

ssh -X nvidia@192.168.0.198

if imincomplete, try to reconnect cameras via camera_config.sh

todo: set id faster than saving
