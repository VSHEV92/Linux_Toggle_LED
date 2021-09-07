#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>

using namespace std;

#define BASEADDR 0x3F200000
#define SEL_OFFSET 0x0
#define SET_OFFSET 0x1C/4
#define CLR_OFFSET 0x28/4

int main (int argc, char* argv[]){

	void *gpio_map;
	volatile unsigned *gpiochip;

	// check parameters number
	if (argc != 2){
		cout << "Need one parameter - gpio line nymber" << endl;
		return 1;
	}
	else if( atoi(argv[1]) < 0 || atoi(argv[1]) > 9) {
		cout << "Valid line number is 0 to 9" << endl;
		return 1;
	}
	int line_number = atoi(argv[1]);

	// map physical addres
	int fd = open("/dev/mem", O_RDWR|O_SYNC);
	if (fd < 0) {
		cout << "Can't open /dev/mem" << endl;
		return 1;
	}
	gpio_map = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, BASEADDR);
	close(fd);

	if (gpio_map == MAP_FAILED){
		cout << "Mmap fail" << endl;
		return 1;
	}
	gpiochip = (volatile unsigned *)gpio_map;

	// set line as output
	*(gpiochip + SEL_OFFSET) |= (1<<(line_number*3));

	// start LED toggle
	while(1){
		*(gpiochip + SET_OFFSET) |= (1<<line_number);
		usleep(200000);
		*(gpiochip + CLR_OFFSET) |= (1<<line_number);
		usleep(200000);
	}

	return 0;
}
