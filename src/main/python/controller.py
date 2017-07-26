import os
import subprocess
import time
import parse_data

number_of_readings_per_device = 4
expected_lines = 0

devices = []
device_ids = dict()

def getActiveDevices():
    active_file  = "src/main/config/active_photons.txt"
    file = open(active_file,"r")
    for line in file:
        devices.append(line[:-1])

def getIds():
    id_file = "src/main/config/photon_ids.txt"
    file = open(id_file, "r")
    for line in file:
        space = line.find(' ')
        device_name = line[0:space]
        core_id = line[space+1:-1]
        device_ids[device_name] = core_id

def turnLEDon():
    time.sleep(.2)
    toggle_led_command = "./src/main/bash/toggle_led.sh" + ' ' + device_id + ' ' + "on"
    os.system(toggle_led_command)
    time.sleep(.2)

def turnLEDoff():
    time.sleep(.2)
    toggle_led_command = "./src/main/bash/toggle_led.sh" + ' ' + device_id + ' ' + "off"
    os.system(toggle_led_command)
    time.sleep(.2)

def turn_all_off():
    turn_all_off_command = "./src/main/bash/turn_all_off.sh"
    os.system(turn_all_off_command);

def start_sensor_data_listener():
    # start background process to log all incoming sensor data
    logging_command = "./src/main/bash/log_colorinfo.sh"
    subprocess.Popen(logging_command)

def capture_sensor_data(expected_lines):
    #tell photons to capture sensor data
    os.system("./src/main/bash/capture_sensors.sh")
    timer = 0
    time.sleep(.05)
    print(expected_lines)
    while(int(os.popen("wc -l < sensor_info.txt").read()) != expected_lines):
        time.sleep(1)
        timer += 1
        if (int(os.popen("wc -l <sensor_info.txt").read()) > expected_lines):
            print("error: received too many sensor readings")
            os.system(">sensor_info.txt")
            return 0
        elif(timer > 4):
            print("error: received too few sensor readings")
            os.system(">sensor_info.txt")
            return 0

    os.system("cat sensor_info.txt >> all_data.txt")
    os.system(">sensor_info.txt")
    return 1

def initialize():
    # start collecting colorinfo
    start_sensor_data_listener()

    # get rid of old intermediary files
    os.system("rm -rf sensor_info.txt")
    os.system("rm -rf all_data.txt")
    turn_all_off()

    # get information about photons
    getActiveDevices()
    getIds()
    
    os.system(">sensor_info.txt")

def parse():
    os.system("mv all_data.txt sensor_info.txt")
    parse_data.generateOutput()
    parse_data.debugger()
    print("parsed data!")


if __name__ == "__main__":

    initialize()
    
    expected_lines = number_of_readings_per_device*len(devices)

    for device in devices:
        device_id = device_ids[device]
    
        turnLEDon()

        while(not capture_sensor_data(expected_lines)):
            time.sleep(2)

        turnLEDoff()

        while (not capture_sensor_data(expected_lines)):
            time.sleep(2)

    parse()
    exit(0)
