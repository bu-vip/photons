# photon
This system collects data from the Photon matrix. It can take data from any number of sensors specified. The current setup turns on each LED in succession and captures sensor reading from all sensors simultaneously. Sensor data is then written to a file on your local computer.

### Requirements:
* Bash shell (for Windows, you need to install Cygwin)
* Python 3.5.2 or higher
* Particle CLI


## First Time Use:
Make sure the bash files are executable:
```bash
cd /path/to/photons/
chmod +x *.sh
```
Flash all the photons:
Open `active_photons.txt` and make sure the file contains the names of photons you are using
```bash
python initialize.py”
```

## Usage:

To run the program: 
```bash
python controller.py
```
This command will generate a raw data file named `sensor_info.txt`
> NOTE: this file gets written over each time the controller is called, so be sure to copy this file over if it contains good data

To format raw_output into convenient text file:
```bash
python parse_data.py
```
This command takes the raw data from `sensor_info.txt` and generates a formatted file named `output.txt`
> NOTE: this file gets written over each time the parse_data.py is called, so be sure to copy this file over if it contains good data

To re-flash the photons:
```bash
python initialize.py
```

