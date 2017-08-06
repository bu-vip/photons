#!/bin/bash
source ~/.profile
particle serial monitor /dev/ttyACM1 > ACM1.txt &
particle serial monitor /dev/ttyACM2 > ACM2.txt &
particle serial monitor /dev/ttyACM3 > ACM3.txt &
particle serial monitor /dev/ttyACM4 > ACM4.txt &
particle serial monitor /dev/ttyACM5 > ACM5.txt &
particle serial monitor /dev/ttyACM6 > ACM6.txt &
particle serial monitor /dev/ttyACM7 > ACM7.txt &
particle serial monitor /dev/ttyACM8 > ACM8.txt &
particle serial monitor /dev/ttyACM0 > ACM0.txt &
wait
