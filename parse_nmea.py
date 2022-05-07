import serial
import math

LAT_INDEX = 3
LONG_INDEX = 5

last_lat = None
last_long = None
current_lat = None
current_long = None

R_earth = 6378100 #in meters


#Coordinates of Bearl
TARGET_LAT = 32.88199100695122
TARGET_LONG = -117.2341503022544
#TARGET_LAT = 33.02441394227215
#TARGET_LONG = -117.08102293451428

def calculateHeading():
	if(last_lat == None or last_long == None):
		print("Insufficient data to calculate heading")
	else:
		dy = math.cos(math.radians(current_lat)) * math.sin(math.radians(current_long - last_long))
		dx = (math.cos(math.radians(last_lat)) * math.sin(math.radians(current_lat))) - (math.sin(math.radians(last_lat)) * math.cos(math.radians(current_lat)) * math.cos(math.radians(current_long - last_long)))

		try:
			heading = math.atan2(dy, dx)
		except Exception:
			heading = 0
			pass
		#distance = math.sqrt(dx**2+dy**2)
		distance = 0
		#print('Heading: ' + str(heading) + '\tDistance ' + str(distance) + '\tdx: ' + str(dx) + '\tdy: ' + str(dy))

#Calculate target heading based on current gps coordinates and desired gps coordinates 0 is North and increases to 360 clockwise
def calculateTargetHeading():
	dy = math.cos(TARGET_LAT*180/math.pi) * math.sin((TARGET_LONG - current_long)*180/math.pi)
	dx = (math.cos(current_lat*180/math.pi) * math.sin(TARGET_LAT*180/math.pi)) - (math.sin(current_lat*180/math.pi) * math.cos(TARGET_LAT*180/math.pi) * math.cos((TARGET_LONG - current_long)*math.pi))
	target_heading = math.atan2(dy, dx)

	#Convert to degrees
	bearing = (target_heading*180/math.pi + 360) % 360
	#print('dx: ' + str(dx) + '\tdy: ' + str(dy))
	#print('Target Heading: ' + str(bearing))

	return bearing


ser = serial.Serial(port='/dev/serial0',
			baudrate = 9600,
			parity = serial.PARITY_NONE,
			stopbits = serial.STOPBITS_ONE,
			bytesize = serial.EIGHTBITS,
			timeout = 1)


def getTargetHeading():
	x = ser.readline()
	x = x.decode('ISO-8859-1')
	if '$GNRMC' in x:
		x = x.split(',')
		lat_degrees = x[LAT_INDEX][0:2]
		lat_minutes = x[LAT_INDEX][2:-1]
		lat = float(lat_degrees) + float(lat_minutes)/60
		if x[LAT_INDEX+1] == 'N':
			pass
		elif x[LAT_INDEX+1] == 'S':
			lat *= -1

		long_degrees = x[LONG_INDEX][0:3]
		long_minutes = x[LONG_INDEX][3:-1]
		long = float(long_degrees) + float(long_minutes)/60
		if x[LONG_INDEX+1] == 'E':
			pass
		elif x[LONG_INDEX+1] == 'W':
			long *= -1

		last_lat = current_lat
		last_long = current_long
		current_long = long
		current_lat = lat

		print('Latitude, Longitude = ' + str(lat) + ', ' + str(long))
		return calculateTargetHeading()
	else:
		print("No GPS data")

def setTargetCoordinates(target_lat, target_long):
	TARGET_LAT = target_lat
	TARGET_LONG = target_long

while 1:
	x = ser.readline()
	x = x.decode('ISO-8859-1')
	if '$GNRMC' in x:
		x = x.split(',')
		lat_degrees = x[LAT_INDEX][0:2]
		lat_minutes = x[LAT_INDEX][2:-1]
		lat = float(lat_degrees) + float(lat_minutes)/60
		if x[LAT_INDEX+1] == 'N':
			pass
		elif x[LAT_INDEX+1] == 'S':
			lat *= -1

		long_degrees = x[LONG_INDEX][0:3]
		long_minutes = x[LONG_INDEX][3:-1]
		long = float(long_degrees) + float(long_minutes)/60
		if x[LONG_INDEX+1] == 'E':
			pass
		elif x[LONG_INDEX+1] == 'W':
			long *= -1

		last_lat = current_lat
		last_long = current_long
		current_long = long
		current_lat = lat

		print('Latitude, Longitude = ' + str(lat) + ', ' + str(long))
		calculateHeading()
		calculateTargetHeading()
