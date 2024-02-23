import serial

arduino_port = "/dev/cu.usbmodem14101"
baud = 9600
fileName = "analogData.csv"
samples = 100
print_labels = False

ser = serial.Serial(arduino_port, baud)
print("Connected to Arduino port: " + arduino_port)
file = open(fileName, "a")
print("Created File")

line = 0

while line <=samples:
	if print_labels:
		if line==0:
			print("Printing Column Headers")

		else:
			print("Line: " + str(line) + ": writing...")
	getData=str(ser.readline())
	data=getData[0:][:-2]
	print(data)
