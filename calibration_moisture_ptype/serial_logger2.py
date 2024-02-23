import serial.tools.list_ports
import time


ports = serial.tools.list_ports.comports()
serialInst = serial.Serial()


port_list = []
my_port = ""
for onePort in ports:
	port_list.append(str(onePort))
	print(str(onePort))
	if "/dev" in str(onePort):
		my_port = onePort

my_port = "/dev/cu.usbmodem14401"
print(f"myPort = {my_port}")

serialInst.baudrate = 9600
serialInst.port = my_port
serialInst.open()
serialInst.flushInput()

air = False
water = False
while True:
	if serialInst.in_waiting:
		if not air:
			airFile = open("airData.txt", "a")
			airFile.write("Time AnalogMoisture Temperature\n")
			command = input("Please expose moisture sensor to air. When done, type y and enter. Only first char will be considered in the response.")
			serialInst.write(command.encode())
			time.sleep(4)
			while not air:
				packet = serialInst.readline().decode('utf-8')
				if "END" not in packet:
					airFile.write(str(time.time()) + " " + packet)
					print(packet)
				else:
					airFile.write(str(time.time()) + " " + packet)
					print(packet)
					airFile.close()
					air = True
					if not water:
						waterFile = open("waterData.txt", "a")
						waterFile.write("Time AnalogMoisture Temperature\n")
						command = input("Please expose moisture sensor to water. When done, type y and enter. Only first char will be considered in the response.")
						serialInst.write(command.encode())
						time.sleep(4)
						while not water:
							packet = serialInst.readline().decode('utf-8')
							if "END" not in packet:
								waterFile.write(str(time.time()) + " " + packet)
								print(packet)
							else:
								waterFile.write(str(time.time()) + " " + packet)
								print(packet)
								waterFile.close()
								water = True
								sampleFile = open("sampleData.txt", "a")
								sampleFile.write("Time AnalogMoisture Temperature percMoisture\n")

		else:
			sampleFile = open("sampleData.txt", "a")
			sampleFile.write(str(time.time()) + " " + packet)
			packet = serialInst.readline().decode('utf-8')
			print(packet)
		
	    	
	 


