#!/bin/bash
# linux toggle led using sysfs

gpio_dir=/sys/class/gpio

echo "Linux Toggle LED"

# check options
while getopts "u" opt; do
	case ${opt} in
		u ) 
			if [ $# -ne 2 ]; then
				echo "Script need 1 parameter - GPIO Pin Number"
			exit
			fi
			echo "Unexport GPIO Pin $2"
			echo $2 > "$gpio_dir/unexport"
			exit
		;;
		\? ) 
			echo "Option -u is unexport GPIO Pin"
			exit
		;;
	esac
done

# check parameter number
if [ $# -ne 1 ]; then
	
	echo "Script need 1 parameter - GPIO Pin Number"
	exit
fi

# check if export is done
if [ ! -d "${gpio_dir}/gpio$1" ]; then
	echo "Export GPIO Pin $1"
	echo $1 > "${gpio_dir}/export"
	sleep 0.1
fi

# set direction
echo out > "${gpio_dir}/gpio$1/direction"

# start led toggle
while [ 1 ]
do
	echo 1 > "${gpio_dir}/gpio$1/value"
	sleep 0.5
	echo 0 > "${gpio_dir}/gpio$1/value"
	sleep 0.5
done
