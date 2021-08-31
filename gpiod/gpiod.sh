# gpio toggle led using libgpiod

# check parameters number
if [ $# -ne 1 ]
then
	echo "Need one parameter - pin number"
	exit 1
fi

# print detected gpiochips
echo "Detected gpiochips:"
gpiodetect

#start led toggle
while [ 1 ]
do
gpioset 0 ${1}=1
sleep 0.1
gpioset 0 ${1}=0
sleep 0.1
done
