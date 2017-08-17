# photons
This system collects data from the Photon matrix. It can take data from any number of sensors specified. The current setup turns on each LED in succession and captures sensor reading from all sensors simultaneously. Sensor data is then written to a file on your local computer.

### Requirements:
* Bash shell (for Windows, you need to install [Cygwin](https://www.cygwin.com/))
* Python 3.5.2 or higher
* [Particle CLI](https://www.particle.io/products/development-tools/particle-command-line-interface)

### Architecture:
The system contains a local computer and an array of photons boards. Each photon board is flashed with a driver and sends data to the local computer using a usb serial connection. The photons listen for certain events using the [Particle Cloud](https://www.particle.io/products/platform/particle-cloud) to execute commands such as "turn on LED" and "run trial". Using Bash scripts, the local publishes commands and then uses a Bash script and then a python parser to parse the sensor readings.

## First Time Use:
1. Make sure the bash files are executable:
```bash
cd /path/to/photons/
chmod +x src/main/bash/*.sh
```

2. Flash all the photons:
Open `src/main/config/active_photons.txt` and make sure the file contains the names of photons you are using
```bash
cd /path/to/photons/
python src/main/python/initialize.py
```

## Usage:

#### To initialize the sensor: 
```bash
cd /path/to/photons/
./src/main/bash/publish_order_numbers.sh
```

#### To run a trial:
1. Make sure the usb serial port is open, the sensors are initialized, and run the log sensors script:
```bash
cd path/to/photons
./src/main/bash/log_sensors.sh
```
This command will generate 9 raw data files named `ACM#.txt` corresponding to each serial port connection. These files contain the outputs of each serial port and are necessary for parsing.
> NOTE: these file gets written over each time the log_sensor.sh is called, so make sure to copy these files over if they contain good data that has not been parsed yet.
2. Send the run_trial event to the photons over the cloud:
```bash
particle publish all_photons run_trial
```
3. Once the trial has completed, stop the log sensors script (Ctrl-C) and run the parser:
```bash
cd path/to/photons
python src/main/python/parse_data.py
```
This command will generate a formatted data file named `timestamp_output.txt`. A raw data file named `data.txt` is also generated, but is used only for debugging purposes.
> NOTE: these file gets written over each time the parser is called, so be sure to copy this file over if it contains good data. 

#### To run 4 trials in succession:
Follow the same format as above, but replace the "run_trial" event in instruction #2 for "run_4":
```bash
particle publish all_photons run_4
```

#### To re-flash the photons:
```bash
cd /path/to/photons/
python src/main/python/initialize.py
```
#### To get testbed dimensions:
```bash
cd /path/to/photons/
g++ -std=c++14 src/main/config/testbed_dimensions.cpp -o testbed_dimensions && ./testbed_dimensions
```
This command will generate a standard output detailing the testbed dimensions
> NOTE: these dimensions need to be modified in the c++ program to match the testbed you have set up. This includes the object location.

