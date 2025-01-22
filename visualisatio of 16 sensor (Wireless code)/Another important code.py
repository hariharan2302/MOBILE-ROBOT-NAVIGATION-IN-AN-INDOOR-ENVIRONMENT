import serial
import time

# Set up the serial port communication
ser = serial.Serial('COM8',115200)  # Replace 'COM3' with the correct serial port name and 9600 with the baud rate used by your Arduino

# Set up the Arduino WiFiESP library
wifi_ser = serial.Serial('COM8',115200)  # Replace 'COM4' with the correct serial port name and 115200 with the baud rate used by your WiFi module
time.sleep(1)

while True:
    # Wait for data from the Arduino
    if ser.in_waiting > 0:
        data = ser.readline().decode('utf-8').rstrip()
        print(data)  # Print the received data to the console

        # Send the received data to the laptop over WiFi
        wifi_ser.write(data.encode('utf-8') + b'\r\n')

    # Check for data received over WiFi
    if wifi_ser.in_waiting > 0:
        data = wifi_ser.readline().decode('utf-8').rstrip()
        print(data)  # Print the received data to the console

        # Send the received data to the Arduino
        ser.write(data.encode('utf-8') + b'\n')
