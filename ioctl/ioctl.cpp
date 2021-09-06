#include<iostream>
#include<linux/gpio.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<unistd.h>

using namespace std;

int main(int argc, char* argv[]){
	int gpio_h, line_h;
	gpiohandle_request req;
	gpiohandle_data data;

	// check parameters number
	if (argc != 2){
		cout << "Need one parameter - gpio line number" << endl;
		return 1;
	}

	// get gpio chip handler
	gpio_h = open("/dev/gpiochip0", O_RDONLY);
	if (gpio_h < 0) {
		cout << "Can't get gpio chip handler" << endl;
		return 1;
	}

	// create request and get line handler
	req.lineoffsets[0] = atoi(argv[1]);
	req.flags = GPIOHANDLE_REQUEST_OUTPUT;
	req.lines = 1;

	line_h = ioctl(gpio_h, GPIO_GET_LINEHANDLE_IOCTL, &req);
	if (line_h < 0) {
		cout << "Can't get line handler" << endl;
		return 1;
	} 

	// start LED toggle
	data.values[0] = 1;
	while (1) {
		ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
		usleep(200000);
		data.values[0] = !data.values[0];
	}

	return 0;
}
