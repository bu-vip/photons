# the names of devices that are being used
devices = []
# maps coreid to name ex: coreid = 2c002b001947353236343033 name = A0
device_ids = dict()
# maps coreid to the an ordered list of sensor readings (in order of time the reading was taken
device_stats = dict()

number_of_readings_per_device = 4

def getActiveDevices():
    active_file  = "src/main/config/active_photons.txt"
    file = open(active_file,"r")
    for line in file:
        devices.append(line[:-1])

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
    line = "   "
    line += "background    "
    for device in devices:
        line += device + "            "
    line += "\n"
    file.write(line)
    for device in devices:
        line = device + " "
        reading_count = 0
        for value in device_stats[device_ids[device]]:
            line += value + " "
            reading_count += 1
            if (reading_count == number_of_readings_per_device):
                reading_count = 0
                line += "  "
        line += "\n"
        file.write(line)
    file.close()

getActiveDevices()
matchNamestoID()
parseRawSensorData()
formatSensorData()

