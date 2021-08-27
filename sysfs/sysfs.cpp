#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>

using namespace std;

int main(int argc, char* argv[]){
	string gpio_dir = "/sys/class/gpio";
	string gpio_pin = "/gpio" + string(argv[1]);
        ofstream fd;
	const int delay = 100000; // 0.1 ms

	// check parameter number
	if (argc != 2){
		cout << "Need one parameter - pin number" << endl;
		return 1;
	}

	// export gpio pin
	fd.open(gpio_dir + "/export");
	if (fd.is_open()){
		fd << argv[1];
		fd.close();
		usleep(100000);
	} else {
		cout << "Can't open " << gpio_dir << "/export" << endl;
		return 1;
	}
	cout << "Export pin " << argv[1] << endl;

	// set pin direction
	fd.open(gpio_dir + gpio_pin + "/direction");
	if (fd.is_open()){
		fd << "out";
		fd.close();
	} else {
		cout << "Can't open " << gpio_dir + gpio_pin << "/direction" << endl;
		return 1;
	}

	//open value file
	fd.open(gpio_dir + gpio_pin + "/value");
	if (!fd.is_open()){
		cout << "Can't open " << gpio_dir + gpio_pin << "/value" << endl;
		return 1;
	}

	// start toggle led
	while(1){
		fd << 1;
		fd.flush();
		usleep(delay);
		fd << 0;
		fd.flush();
		usleep(delay);
	}
    return 0;
}
