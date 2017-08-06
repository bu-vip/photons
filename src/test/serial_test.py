import os
import subprocess
import time
subprocess.Popen("../main/bash/log_colorinfo.sh")
start = time.clock()
for i in range(0,10):
    os.system("particle call 2e0020000a47353235303037 led_on") 
    os.system("../main/bash/capture_sensors.sh")
    os.system("particle call 2e0020000a47353235303037 led_off") 
    os.system("../main/bash/capture_sensors.sh")
print(time.clock() - start)
