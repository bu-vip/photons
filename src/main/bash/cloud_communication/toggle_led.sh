#!/bin/bash
source ~/.profile
DEVICE=$1
STATE=$2
if [ $STATE == 'on' ]; then
  particle publish $DEVICE 'led_on';
fi
if [ $STATE != 'on' ]; then
  particle publish $DEVICE 'led_off';
fi
