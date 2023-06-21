import serial

# Define the serial port and baud rate
serial_port = '/dev/ttyUSB0'  # Replace with the actual serial port
baud_rate = 9600  # Replace with the baud rate of your device

# Create a serial object
ser = serial.Serial(serial_port, baud_rate)

# Infinite loop to listen for data
while True:
    if ser.in_waiting > 0:
        # Read data from the serial port
        data = ser.readline().decode().rstrip()
        
        # Print the received data
        print(data)
