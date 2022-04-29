#include "main.h"

#define PI 3.14159265

//MUST RUN AS SUDO

//Calibration Parameters
#define MAG_X_OFFSET 25
#define MAG_Y_OFFSET 104

HMC5883L mag;
int16_t mx, my, mz;
int16_t mx_max, my_max, mx_min, my_min;

void calibrateCompass() {
	int i;

	mag.getHeading(&mx, &my, &mz);
	mx_max = mx;
	mx_min = mx;
	my_max = my;
	my_min = my;

	for(i = 0; i < 2000; i++) {
		mag.getHeading(&mx, &my, &mz);
		if(mx > mx_max) {
			mx_max = mx;
		}
		else if(mx < mx_min) {
			mx_min = mx;
		}

		if(my > my_max) {
			my_max = my;
		}
		else if(my < my_min) {
			my_min = my;
		}
		bcm2835_delay(10);
	}

	printf("mx_max: %d\nmx_min: %d\nmy_max: %d\nmy_min%d\n", mx_max, mx_min, my_max, my_min);
}

int main() {
	printf("Beginning Main\n");

	I2Cdev::initialize();
	printf("I2Cdev initialized\n");
	I2Cdev::enable(false);
	printf("I2Cdev enabled\n");

		if(mag.testConnection()) {
			printf("HMC5883L connection test successful\n");
		}
		else {
			printf("HMC5883L connection failed. Terminating\n");
			return 1;
		}

	mag.initialize();
	int8_t mag_averaging = mag.getSampleAveraging();
	printf("Mag averaging: %d\n", mag_averaging);
	mag.setSampleAveraging(HMC5883L_AVERAGING_8);
	mag.setGain(HMC5883L_GAIN_1370);

	if(0) {
		printf("Calibrating compass in 3 seconds\n");
		printf("\n");
		bcm2835_delay(3000);
		calibrateCompass();
	}

	float heading;
	while(1) {
		mag.getHeading(&mx, &my, &mz);
		mx += MAG_X_OFFSET;
		my += MAG_Y_OFFSET;
		int16_t tmp = my;
		
		//rotate readings 90deg ccw
		my = mx;
		mx = -tmp;
		
		//heading with North equals 0 degrees and range of -180 to 180
		heading = atan2(my, mx) * 180 / PI;
		//convert to range of 0 to 360
		heading = heading < 0 ? heading + 360 : heading;
		printf("  mx:  %d       my:  %d      mz:  %d     heading:  %3.1f deg\r", mx, my, mz, heading);
    		fflush(stdout);
    		bcm2835_delay(200);
	}

	return 1;
}
