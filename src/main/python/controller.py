import os
import subprocess
import parse_data
import time

def connect_serial_ports():
    subprocess.Popen("src/main/bash/log_sensors.sh")
    sensors_logged = input("Press Enter when all serial ports detected")

def set_order_numbers():
    order_set = "n"
    while(order_set != ""):
        os.system("./src/main/bash/publish_order_numbers.sh")
        order_set = input("Press Enter when orders published")

def run_trial():
    os.system("particle publish all_photons run_trial")

connect_serial_ports()
set_order_numbers()
run_trial()
time.sleep(10)
parse_data.generateOutput()
