#!/usr/bin/env python3
import serial
import pynmea2
import rospy
from sensor_msgs.msg import NavSatFix
from pynmea2.nmea import ChecksumError
import random

def start():
    global gps_pub, nav_msg
    rospy.init_node('gps_node')
    gps_frame_id='main_gps_sensor_link'
    gps_pub = rospy.Publisher('/robot/main_gps_fix', NavSatFix, queue_size=10)
    com_port = rospy.get_param("~com_port", "/dev/ttyACM1")
    baud = rospy.get_param("~baud", 38400)

    try:
        ser = serial.Serial(com_port, baudrate=baud, timeout=0.2)
    except serial.SerialException as e:
        rospy.logerr(f"Failed to open serial port {com_port} at {baud} baud: {e}")
        return

    nav_msg = NavSatFix()
    nav_msg.header.seq = 0
    nav_msg.header.frame_id = gps_frame_id
    nav_msg.status.service = 1
    nav_msg.position_covariance_type = 2

    while not rospy.is_shutdown():
        try:
            line = ser.readline()
            line = str(line, encoding='utf-8')
            line = line.strip()
            #print(line)
        except serial.SerialException as e:
            rospy.logerr(f"Error reading from serial port {com_port}: {e}")
            continue

        nav_msg.header.stamp = rospy.get_rostime()
        if (line[1:6] == 'GPGGA'):
            try:
                msg = pynmea2.parse(line)
                #print(msg.gps_qual)                
                if msg.gps_qual == 5 or msg.gps_qual == 4 or msg.gps_qual == 1:
                    nav_msg.latitude = msg.latitude
                    nav_msg.longitude = msg.longitude
                    nav_msg.altitude = msg.altitude
                    nav_msg.status.status = msg.gps_qual
                    gps_pub.publish(nav_msg)
                else:
                    # # rospy.logwarn('Non fix GPS - check base')
                    nav_msg.latitude = random.uniform(44.1000,78.1000)
                    nav_msg.longitude = random.uniform(44.1000,78.1000)
                    nav_msg.altitude = 312.0
                    nav_msg.status.status = 0
                    gps_pub.publish(nav_msg)
            except (ChecksumError, pynmea2.nmea.ParseError) as e:
                rospy.logerr(f"Checksum or parse error in line: {line}, Error: {e}")


if __name__ == '__main__':
    start()
