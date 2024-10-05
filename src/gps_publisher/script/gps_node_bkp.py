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
    gps_pub = rospy.Publisher('main_gps_fix', NavSatFix, queue_size=10)
    com_port = rospy.get_param("~com_port", "/dev/ttyS3")
    baud = rospy.get_param("~baud", 9200)
    bd_test = baud
    ser = serial.Serial(com_port, baudrate=bd_test, timeout=0.2)
    # rand_gps = random.uniform(44.1000,78.1000)

    nav_msg = NavSatFix()
    nav_msg.header.seq = 0
    nav_msg.header.frame_id = gps_frame_id
    nav_msg.status.service = 1
    nav_msg.position_covariance_type = 2

    while not rospy.is_shutdown():
        line = ser.readline()
        line = str(line, encoding='utf-8')
        line = line.strip()
        # rand_gps = random.uniform(44.1000,78.1000)
        nav_msg.header.stamp = rospy.get_rostime()
        if (line[1:6] == 'GPGGA'):
            try:
                msg = pynmea2.parse(line)
                if msg.gps_qual == 4:
                    nav_msg.latitude = msg.latitude
                    nav_msg.longitude = msg.longitude
                    nav_msg.altitude = msg.altitude
                    nav_msg.status.status = msg.gps_qual
                if msg.gps_qual != 4:
                    # print('Non fix GPS- check base')
                    nav_msg.latitude = random.uniform(44.1000,78.1000)
                    nav_msg.longitude = random.uniform(44.1000,78.1000)
                    nav_msg.altitude = 312.0
                    nav_msg.status.status = msg.gps_qual
            except ChecksumError:
                print(f'Checksum error in line: {line}')

        if (line[1:6] == 'GPGST'):
            gst_string = line.split(',')
            lat_acc = 0.0 if len(gst_string[6]) == 0 else float(gst_string[6])
            lon_acc = 0.0 if len(gst_string[7]) == 0 else float(gst_string[7])
            alt_acc = 0.0 if len(gst_string[8][0:-3]) == 0 else float(gst_string[8][0:-3])
            nav_msg.position_covariance[0] = (lat_acc) ** 2
            nav_msg.position_covariance[4] = (lon_acc) ** 2
            nav_msg.position_covariance[8] = (alt_acc) ** 2

        gps_pub.publish(nav_msg)

if __name__ == '__main__':
    start()
