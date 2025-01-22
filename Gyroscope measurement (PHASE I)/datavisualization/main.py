import serial
import time
import matplotlib.pyplot as plt
import cv2
path = r"D:\Downloads\gridbackground.jpg"
# make sure the 'COM#' is set according the Windows Device Manager
ser = serial.Serial('COM5', 9600, timeout=1)
time.sleep(2)

for i in range(100000000):
    line = ser.readline()   # read a byte
    if line:
        string = line.decode()  # convert the byte string to a unicode string
        str= string.split(",")
        str1=str[0]
        str2=str[1].rstrip()

        num1 = float(str1)
        num2 = float(str2)# convert the unicode string to an int
        print(num1,num2)
        image = cv2.imread(path)
        window_name = 'Image'
        # print("X")
        x = int(100)
        # print("Y")
        # y = int(input())
        center_coordinates = (int(num1)+10,int(num2)+10)
        radius = 8
        color = (255, 0, 0)
        thickness = 1
        image = cv2.circle(image, center_coordinates, radius, color, thickness)
        cv2.imshow(window_name, image)
        cv2.waitKey(5)
        # plt.plot(num1,num2)
        # plt.xlabel('Time (seconds)')
        # plt.ylabel('Potentiometer Reading')
        # plt.title('Potentiometer Reading vs. Time')
        # plt.show()
ser.close()