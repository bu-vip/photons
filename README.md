# photons
This system collects data from the Photon matrix. It can take data from any number of sensors specified. The current setup turns on each LED in succession and captures sensor reading from all sensors simultaneously. Sensor data is then written to a file on your local computer.

### Requirements:
* Bash shell (for Windows, you need to install [Cygwin](https://www.cygwin.com/))
* Python 3.5.2 or higher
* [Particle CLI](https://www.particle.io/products/development-tools/particle-command-line-interface)

### Architecture:
The system contains a local computer and an array of photons boards. Each photon board is flashed with a driver and communicates to the local computer using the [Particle Cloud](https://www.particle.io/products/platform/particle-cloud). The photons listen for certain events to execute commands such as "turn on LED" and posts data such as sensor readings to the Particle Cloud. The main program runs on your local computer. It is written in Python which calls individual bash scripts to communicate with the Photons boards through the Particle Cloud.

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

#### To run the program: 
```bash
cd /path/to/photons/
python src/main/python/controller.py
```
This command will generate a formatted data file named `output.txt`. A raw data file named `sensor_info.txt` is also generated, but is used only for debugging purposes.
> NOTE: these file gets written over each time the controller is called, so be sure to copy this file over if it contains good data. 

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

