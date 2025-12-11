#!/usr/bin/env bash
##############################################################
# Filename    : LightWater.sh
# Description : Use LEDBar Graph(10 LED)
# Author      : www.freenove.com (Bash by Nick)
# Modification: December 9, 2025
#############################################################

declare -a ledpin=(17 18 27 22 23 24 25 2 3 8)
declare -a backwardsled=(8 3 2 25 24 23 22 27 18 17)
sleep="0.1"
ON=1
OFF=0


#This is to make sure all lights start as off
# and that pin is able to be used as output for the led pins
for pin in "${ledpin[@]}"; do
	gpio mode "$pin" out
	gpio write "$pin" $OFF
done

echo "The program is starting, please press ctrl-c to end the program"

while true; do
	#make led go from left to right
	for pin in "${ledpin[@]}"; do
		gpio write "$pin" ${ON}
		sleep $sleep
		gpio write "$pin" ${OFF}
	done
	#make led go from right to left
	for pin in "${backwardsled[@]}"; do
		gpio write "$pin" ${ON}
		sleep $sleep
		gpio write "$pin" ${OFF}
	done

done

exit 0	
