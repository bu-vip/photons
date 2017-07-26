import os
# the names of devices that are being used
devices = []
device_locations = ["A1", "A2", "A3", "B1", "B2", "B3", "C1", "C2", "C3"]
# maps coreid to name ex: coreid = 2c002b001947353236343033 name = A0
device_ids = dict()
# maps coreid to the an ordered list of sensor readings (in order of time the reading was taken
device_stats = dict()

number_of_readings_per_device = 8

def getActiveDevices():
    active_file  = "src/main/config/active_photons.txt"
    file = open(active_file,"r")
    for line in file:
        devices.append(line[:-1])
    print(devices)

def matchNamestoID():
    id_file = "src/main/config/photon_ids.txt"
    file = open(id_file, "r")
    for line in file:
        space = line.find(' ')
        device_name = line[0:space]
        core_id = line[space+1:-1]
        device_ids[device_name] = core_id

def parseRawSensorData():
    file = "sensor_info.txt"
    f = open(file,"r")
    for line in f:
        if "lux" in line:
            lux_value = line[(line.find("lux = ") + 6): line.find("\",\"ttl")]
            core_id = line[(line.find("coreid\":")+ 9): line.find("\"}")]
            if (core_id in device_stats):
                lux_array = device_stats.get(core_id)
                lux_array.append(lux_value)
                device_stats[core_id] = lux_array
            else:
                lux_array = []
                lux_array.append(lux_value)
                device_stats[core_id] = lux_array

# this function takes the dictionary of lux values and creates a matrix
def formatSensorData():
    output_file = "output.txt"
    file = open(output_file,"w")
    line = "     "
    for device in device_locations:
        line += device + "    "
    line += "\n"
    file.write(line)
    for i in range(0,len(device_locations)):
        line = "\n" + device_locations[i] + "   "
        for j in range(0,number_of_readings_per_device):
            if ( j == 4):
                line = "\nbg   "
            for device in devices:
                num = device_stats[device_ids[device]][number_of_readings_per_device*i+j]
                if(int(num) < 10):
                    line += num + "     "
                elif (int(num) < 100):
                    line += num + "    "
                else:
                    line += num + "   "
            line += "\n"
            file.write(line)
            line = "     "

def formatSensorData_old():
    output_file = "output.txt"
    file = open(output_file,"w")
    light_sources = []
    #light_sources.append("bg")
    line = "    "
    light_sources.append("A1")
    for device in device_locations:
        #light_sources.append(device)
        line += device + "   "
    line += "\n"
    file.write(line)
    for i in range(0,len(light_sources)):
        line = light_sources[i] + "  "
        for j in range(0,number_of_readings_per_device):
            for device in devices:
                line += (device_stats[device_ids[device]][number_of_readings_per_device*i+j]) + "  "
            line += "\n"
            file.write(line)
            line = "    "
            #reading_count = 0
            #if (device_ids[device] in device_stats.keys()): # check if the sensor is one of the active photons
            #    for value in device_stats[device_ids[device]]:
            #        line += value + " "
            #        reading_count += 1
            #        if (reading_count == number_of_readings_per_device):
            #            reading_count = 0
            #            line += "  "
        line += "\n"
        file.write(line)
        line += "bg  "
        for j in range(number_of_readings_per_device,2*number_of_readings_per_device+1):
            for device in devices:
                line += (device_stats[device_ids[device]][number_of_readings_per_device*i+j]) + "  "
            line += "\n"
            file.write(line)
            line = "    "
        line += "\n"
        file.write(line)

    file.close()


def generateOutput():
    os.system(">output.txt")
    matchNamestoID()
    getActiveDevices()
    parseRawSensorData()
    formatSensorData()

# prints output.txt to command line
def debugger():
    output_file = "output.txt"
    file = open(output_file,"r")
    data = file.read()
    print(data)

if __name__ == "__main__":
    generateOutput()
    debugger()
