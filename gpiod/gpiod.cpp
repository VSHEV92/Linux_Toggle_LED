#include<iostream>
#include<gpiod.h>
#include<unistd.h>
#include<string>

int main(int argc, char* argv[]){

	const char* chip_path = "/dev/gpiochip0";
	gpiod_chip* chip = NULL;
	gpiod_line* pin = NULL;
	bool value = 0;	
	std::string str = argv[1];

	// check parameters number
	if (argc != 2){
		std::cout<<"Need one parameter - pin number"<<std::endl;
		return 1;
	}

	// open chip 0
	chip = gpiod_chip_open(chip_path);
	if (!chip){
		std::cout<<"Can't open gpiochip0"<<std::endl;
		return 1;
	}

	//  get line
	pin = gpiod_chip_get_line(chip, std::stoi(str) );
	if (!pin){
		std::cout<<"Can't get gpio line"<<std::endl;
		return 1;
	}

	// start Led toggle
	while (1){
		// request line
		gpiod_line_request_output(pin, "gpiod_test", 0);

		//set value
		gpiod_line_set_value(pin, value);

		//release line
		gpiod_line_release(pin);

		usleep(100000);
		value = !value;
	}

	return 0;
}
