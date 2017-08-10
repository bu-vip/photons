import os
import datetime
import numpy as np

device_ids = dict()
device_stats = dict()
devices = []
number_of_readings_per_device = 4
output_file = ""

def clean_up():
    global device_ids
    global device_stats
    device_ids = dict()
    device_stats = dict()


def match_name_to_id():
    id_file = "src/main/config/photon_ids.txt"
    file = open(id_file, "r")
    for line in file:
        space = line.find(' ')
        device_name = line[0:space]
        core_id = line[space+1:-1]
        device_ids[device_name] = core_id

def parse_raw_data():
    os.system("cat ACM*.txt > data.txt")
    file = open("data.txt", "r")
    for line in file:
        if line[0].isdigit():
            core_id = line[0:line.find(" ")]
            lux_value = line[line.find(" ")+1:len(line)]
            if core_id in device_stats:
                lux_array = device_stats.get(core_id)
                lux_array.append(int(lux_value))
                device_stats[core_id] = lux_array
            else:
                lux_array = []
                lux_array.append(int(lux_value))
                device_stats[core_id] = lux_array

def file_format():
    # create ordered list of relevant device names
    device_stats_keys = device_stats.keys()
    devices_temp = []
    for device_name in device_ids.keys():
        if device_ids[device_name] in device_stats_keys:
            devices_temp.append(device_name)
    devices = sorted(devices_temp)


    # generate output file name
    date = datetime.datetime.now()
    global output_file
    output_file = str(date.hour) + "_" + str(date.minute) + "_output.txt"
    file = open(output_file,"w")


    current_trial = 0
    vals_per_trial = 2*number_of_readings_per_device*len(devices)
    number_of_trials = len(device_stats[device_ids[devices[0]]]) / (vals_per_trial)
    while(current_trial < number_of_trials):
        line = "Trial #" +  str(current_trial + 1) + "-------------------------\n\n"
        file.write(line)
        # create name labels line
        line = "     "
        for device in devices:
            line += device + "    "
        line += "\n"
        file.write(line)
        for i in range(0,len(devices)):
            line = "\n" + devices[i] + "   "
            for j in range(0,number_of_readings_per_device*2):
                if ( j == 4):
                    line = "\nbg   "
                for device in devices:
                    num = device_stats[device_ids[device]][number_of_readings_per_device*2*i+j + current_trial*vals_per_trial]
                    if(num < 10):
                        line += str(num) + "     "
                    elif (num < 100):
                        line += str(num) + "    "
                    else:
                        line += str(num) + "   "
                line += "\n"
                file.write(line)
                line = "     "
        file.write("\n\n")
        current_trial += 1

def LTM_format():
    # create ordered list of relevant device names
    device_stats_keys = device_stats.keys()
    devices_temp = []
    matrix = []
    avg_perturbation = []
    A = []
    b = []
    for device_name in device_ids.keys():
        if device_ids[device_name] in device_stats_keys:
            devices_temp.append(device_name)
    devices = sorted(devices_temp)
    for i in range(0,len(device_stats[device_ids[devices[0]]])/number_of_readings_per_device):
        for device in devices:
            for j in range(0,number_of_readings_per_device):
                values.append(device_stats[device_ids[device]][number_of_readings_per_device*i+j])
            avg_value = np.mean(values)
            values = []
            avg_perturbation.append(avg_value)
        matrix.append(avg_perturbation)
        avg_perturbation = []
        if (len(matrix) == 2*len(devices)):
            A.append(np.subtract(matrix[0:9],matrix[9:]))
            b.append(matrix[8:])
            print(A)
            print(b)
            matrix = []
            




# prints output.txt to command line
def debugger():
    file = open(output_file,"r")
    data = file.read()
    print(data)

def generateOutput():
    clean_up()
    match_name_to_id()
    parse_raw_data()
    file_format()

if __name__ == "__main__":
    generateOutput()
    debugger()
