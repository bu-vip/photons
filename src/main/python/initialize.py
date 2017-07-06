import os
import time

number_of_readings_per_device = 4
photon_program = "src/main/photon-driver/"

devices = []
device_ids = dict()

def getActiveDevices():
    active_file  = "src/main/config/active_photons.txt"
    file = open(active_file,"r")
    for line in file:
        devices.append(line[:-1])


getActiveDevices()

for device in devices:
    flash_command = "./src/main/bash/flash.sh " + device + ' ' + photon_program
    os.system(flash_command);
print("Waiting 20s for photon boards to fully reset")
time.sleep(20)
