import os
import subprocess
import time
import parse_data

number_of_readings_per_device = 4

all_active_devs = 0
devices = []
device_ids = dict()

def getActiveDevices():
    active_file  = "src/main/config/active_photons.txt"
    file = open(active_file,"r")
    for line in file:
        devices.append(line[:-1])

def findAllDevices():
    listenforPhotons = "./src/main/bash/log_photons.sh"
    subprocess.Popen(listenforPhotons)
    ping_all = "./src/main/bash/ping_all.sh"
    os.system(ping_all)
    time.sleep(2)
    all_active_devs = int(os.popen("wc -l < log_photons.txt").read()) - 2
    os.system("rm log_photons.txt")

def getIds():
    id_file = "src/main/config/photon_ids.txt"
    file = open(id_file, "r")
    for line in file:
        space = line.find(' ')
        device_name = line[0:space]
        core_id = line[space+1:-1]
        device_ids[device_name] = core_id

def turnLEDon():
    toggle_led_command = "./src/main/bash/toggle_led.sh" + ' ' + device_id + ' ' + "on"
    os.system(toggle_led_command)

def turnLEDoff():
    toggle_led_command = "./src/main/bash/toggle_led.sh" + ' ' + device_id + ' ' + "off"
    os.system(toggle_led_command)

def start_sensor_data_listener():
    # start background process to log all incoming sensor data
    logging_command = "./src/main/bash/log_colorinfo.sh"
    subprocess.Popen(logging_command)

def all_sensor_data_arrived(expected_lines):
    timer = 0
    while(int(os.popen("wc -l < sensor_info.txt").read()) < expected_lines):
        time.sleep(.05)
        timer = timer + 1
        if (timer > 40): # wait for data for 2 secs
            return 0
    return 1


os.system("rm -rf sensor_info.txt")

getActiveDevices()
findAllDevices()
getIds()

start_sensor_data_listener()

# tell photons to get background reading
os.system("./src/main/bash/capture_sensors.sh")

expected_lines = 2+all_active_devs*number_of_readings_per_device
if (not all_sensor_data_arrived(expected_lines)):
    print("not all sensor readings were received. Are you sure all photons are connected?")
    exit(1)


for device in devices:
    device_id = device_ids[device]

    turnLEDon()

    #tell photons to capture sensor data
    os.system("./src/main/bash/capture_sensors.sh")

    # wait until all sensor readings have arrived
    timer = 0
    expected_lines += all_active_devs*number_of_readings_per_device
    if (not all_sensor_data_arrived(expected_lines)):
        print("not all sensor readings were received. Are you sure all photons are connected and initialized?")
        exit(1)

    turnLEDoff()

parse_data.generateOutput()


exit(0)