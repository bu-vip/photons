#!/bin/bash
source ~/.profile
particle subscribe colorinfo |& tee -a sensor_info.txt
