from parse_nmea import getTargetHeading

def main():
    print('Main')
    compass = hmc5883l(gauss = 4.7, declination = (0,0))
    while 1:
        #Get heading based on GPS and compass readings
        target_heading = parse_nmea.getTargetHeading
        print('Target Heading: ' + str(getTargetHeading()))

        current_heading = compas.degrees(compass.heading())
        sys.stdout.write("\rCurrent Heading: " + str(current_heading) + "     ")

        #Find difference between the two
        error = target_heading - current_heading[0]
        print('Error: ' + error)


if __name__ == '__main__':
    main()