#include<iostream>
#include<wiringPi.h>

using namespace std;

int main (int argc, char* argv[]){
	// check parameters number
	if (argc != 2){
		cout << "Need one parameter - gpio line number" << endl;
		return 1;
	}
	int line = atoi(argv[1]);
	wiringPiSetup();

	// set line as output
	pinMode(line, OUTPUT);

	// start LED toggle
	while(1) {
		digitalWrite(line, 1);
		delay(200);
		digitalWrite(line, 0);
		delay(200);
	}
	return 0;
}
