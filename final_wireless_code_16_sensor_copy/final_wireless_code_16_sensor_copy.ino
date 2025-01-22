// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include <Mouse.h>
#include <NewPing.h>
#include <WiFiEsp.h>
#include <WiFiEspUdp.h>


Adafruit_MPU6050 mpu;
unsigned long prev=0;
int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;
float gyy=0;
float bx,by,bz;
float cx,cy,cz;
float dx,dy,dz;
float s, lv;
float sy, lvy, sz, lvz;
float aa,ab,ac, chax=0;
float chay=0;
float chaz=0;
float cherror;
int count=0;
float inv=0, invy=0, invz=0;
#define LED_PIN 13
bool blinkState = false;
unsigned long previousMillis = 0;
//Motor A
const int inputPin1  = 10;    // Pin 15 of L293D IC
const int inputPin2  = 11;    // Pin 10 of L293D IC
//Motor B
const int inputPin3  = 9;   // Pin  7 of L293D IC
const int inputPin4  = 8;   // Pin  2 of L293D IC


// Wi-Fi settings
char ssid[] = "Ganesh";
char password[] = "11111111";
IPAddress serverIP(192, 168, 223, 183); // Replace with the IP address of your server
unsigned int serverPort = 139; // Replace with the port number of your server

// Ultrasonic sensor settings
#define TRIGGER_PIN1 2
#define ECHO_PIN1 3
#define MAX_DISTANCE1 5000

#define TRIGGER_PIN2 4
#define ECHO_PIN2 5
#define MAX_DISTANCE2 5000

#define TRIGGER_PIN3 6
#define ECHO_PIN3 7
#define MAX_DISTANCE3 5000

#define TRIGGER_PIN4 44
#define ECHO_PIN4 45
#define MAX_DISTANCE4 5000

#define TRIGGER_PIN5 46
#define ECHO_PIN5 47
#define MAX_DISTANCE5 5000

#define TRIGGER_PIN6 48
#define ECHO_PIN6 49
#define MAX_DISTANCE6 5000

#define TRIGGER_PIN7 36
#define ECHO_PIN7 37
#define MAX_DISTANCE7 5000

#define TRIGGER_PIN8 38
#define ECHO_PIN8 39
#define MAX_DISTANCE8 5000

#define TRIGGER_PIN9 40
#define ECHO_PIN9 41
#define MAX_DISTANCE9 5000

#define TRIGGER_PIN10 22
#define ECHO_PIN10 23
#define MAX_DISTANCE10 5000

#define TRIGGER_PIN11 24
#define ECHO_PIN11 25
#define MAX_DISTANCE11 5000

#define TRIGGER_PIN12 26
#define ECHO_PIN12 27
#define MAX_DISTANCE12 5000

#define TRIGGER_PIN13 28
#define ECHO_PIN13 29
#define MAX_DISTANCE13 5000

#define TRIGGER_PIN14 30
#define ECHO_PIN14 31
#define MAX_DISTANCE14 5000

#define TRIGGER_PIN15 32
#define ECHO_PIN15 33
#define MAX_DISTANCE15 5000

#define TRIGGER_PIN16 34
#define ECHO_PIN16 35
#define MAX_DISTANCE16 5000

// Create objects for ultrasonic sensor and UDP client
NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE1);
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE2);
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE3);
NewPing sonar4(TRIGGER_PIN4, ECHO_PIN4, MAX_DISTANCE4);
NewPing sonar5(TRIGGER_PIN5, ECHO_PIN5, MAX_DISTANCE5);
NewPing sonar6(TRIGGER_PIN6, ECHO_PIN6, MAX_DISTANCE6);
NewPing sonar7(TRIGGER_PIN7, ECHO_PIN7, MAX_DISTANCE7);
NewPing sonar8(TRIGGER_PIN8, ECHO_PIN8, MAX_DISTANCE8);
NewPing sonar9(TRIGGER_PIN9, ECHO_PIN9, MAX_DISTANCE9);
NewPing sonar10(TRIGGER_PIN10, ECHO_PIN10, MAX_DISTANCE10);
NewPing sonar11(TRIGGER_PIN11, ECHO_PIN11, MAX_DISTANCE11);
NewPing sonar12(TRIGGER_PIN12, ECHO_PIN12, MAX_DISTANCE12);
NewPing sonar13(TRIGGER_PIN13, ECHO_PIN13, MAX_DISTANCE13);
NewPing sonar14(TRIGGER_PIN14, ECHO_PIN14, MAX_DISTANCE14);
NewPing sonar15(TRIGGER_PIN15, ECHO_PIN15, MAX_DISTANCE15);
NewPing sonar16(TRIGGER_PIN16, ECHO_PIN16, MAX_DISTANCE16);
WiFiEspUDP udp;

void setup() 
{
  // initialize serial for debugging
  Serial.begin(9600);

  // initialize device
//Ser

if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  
// verify connection
//Serial.println("Testing device connections...");
//Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
for(int i=0;i<20;i++)
{
 sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  ax=a.acceleration.x;
 ay=a.acceleration.y;
 az=a.acceleration.z;
 chax=chax+ax;
 chay=chay+ay;
 chaz=chaz+az;
}

chax=(float)chax;

chay=(float)chay;

chaz=(float)chaz;

//Serial.println("New Chax");
//Serial.print(chax);



   // set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  // set gyro range to +- 500 deg/s
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // set filter bandwidth to 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_10_HZ);
  pinMode(inputPin1, OUTPUT);
    pinMode(inputPin2, OUTPUT);
    pinMode(inputPin3, OUTPUT);
    pinMode(inputPin4, OUTPUT);  
    
  // initialize serial for ESP module
  Serial3.begin(115200);
  WiFi.init(&Serial3);

  // Connect to Wi-Fi
  if (WiFi.begin(ssid, password) == WL_CONNECTED) {
    Serial.println("Connected to Wi-Fi");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Failed to connect to Wi-Fi");
    while (1);
  }
  udp.begin(serverPort);
}

void loop() {

  // read raw accel/gyro measurements from device
  count=count+1;
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);  
bx=(float)a.acceleration.x;
by=(float)a.acceleration.y;
bz=(float)a.acceleration.z;
bx=(bx-chax);
by=(by-chay);
bz=(bz-chaz);

  //Motion in one simple direction, let y=0.
unsigned long currentMillis = millis(); //record time of new reading
float interval = float((float(currentMillis) - float(previousMillis))/1000) ; //Time of previous reading-Time of Current reading= Interval
if(bx>1||bx<(-1))
{
aa=abs(bx)*interval; //acceleration x time=velocity
//ac=(bx)*interval;
lv=inv; // initial velocity=lv, final velocity=inv
inv=inv+aa; // vf =vi+1t;
s=s+(lv*interval)+0.5*aa*interval; // Distance= Previous Distance + Vit + 1/2 x a x t^2

}

if(by>1||by<(-1)){
ab=abs(by)*interval;
//ac=(by)*interval;
lvy=invy;
invy=invy+ab;

sy=sy+(lvy*interval)+0.5*ab*interval;
}

if(bz>1||bz<(-1))
{
ac=abs(bz)*interval;

lvz=invz;
invz=invz+ac;

sz=sz+(lvz*interval)+0.5*ac*interval;
}

  delay(0); // Adjust the delay according to your needs

  // Read distance from the ultrasonic sensor
  unsigned int distance1 = sonar1.ping_cm();
  unsigned int distance2 = sonar2.ping_cm();  
  unsigned int distance3 = sonar3.ping_cm();  
  unsigned int distance4 = sonar4.ping_cm();  
  unsigned int distance5 = sonar5.ping_cm();  
  unsigned int distance6 = sonar6.ping_cm();  
  unsigned int distance7 = sonar7.ping_cm();  
  unsigned int distance8 = sonar8.ping_cm();  
  unsigned int distance9 = sonar9.ping_cm();  
  unsigned int distance10 = sonar10.ping_cm();  
  unsigned int distance11 = sonar11.ping_cm();  
  unsigned int distance12 = sonar12.ping_cm();  
  unsigned int distance13 = sonar13.ping_cm();  
  unsigned int distance14 = sonar14.ping_cm();  
  unsigned int distance15 = sonar15.ping_cm();  
  unsigned int distance16 = sonar16.ping_cm();  

  // Prepare the data to send
  String data1 = String(distance1);
  String data2 = String(distance2);
  String data3 = String(distance3);
  String data4 = String(distance4);
  String data5 = String(distance5);
  String data6 = String(distance6);
  String data7 = String(distance7);
  String data8 = String(distance8);
  String data9 = String(distance9);
  String data10 = String(distance10);
  String data11 = String(distance11);
  String data12 = String(distance12);
  String data13 = String(distance13);
  String data14 = String(distance14);
  String data15 = String(distance15);
  String data16 = String(distance16);
  String data17 = String(s);
  String data18 = String(sy);
  String data19 = String(bx);
  String data20 = String(by);
  // Send the data via UDP
  udp.beginPacket(serverIP, serverPort);

  udp.print(data1+","+data2+","+data3+","+data4+","+data5+","+data6+","+data7+","+data8+","+data9+","+data10+","+data11+","+data12+","+data13+","+data14+","+data15+","+data16+","+data17+","+data18+","+data19+","+data20);
  udp.endPacket();

  Serial.print("Distance: ");
  Serial.print(bx);
  Serial.println(by);

  previousMillis=millis(); //record current time

// blink LED to indicate activity
blinkState = !blinkState;
digitalWrite(LED_PIN, blinkState);
digitalWrite(inputPin1, HIGH);
    digitalWrite(inputPin2, LOW);
    digitalWrite(inputPin3, HIGH);
    digitalWrite(inputPin4, LOW); 

    delay(0);
}
