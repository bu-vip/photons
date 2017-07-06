#!/bin/bash
source ~/.profile
DEVICE="$1"
PROGRAM="$2"
particle flash $DEVICE $PROGRAM

