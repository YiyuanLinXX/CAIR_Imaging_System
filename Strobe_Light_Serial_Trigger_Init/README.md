# Strobe Light Serial Trigger

This is a script for Arduino. You will need to upload this `.ino` to Arduino and connect the cables of cameras and strobe lights to the corresponding pins on Arduino. The arduino will be initialized to set the charge pin and discharge pin of the strobe light to LOW, and the camera trigger pin to HIGH. When your device send 's' through the serial port to Arduino, it will start to sending trigger signals; and when your device send 'e', the Arduino will stop sending trigger signals and recover to initialized status.
