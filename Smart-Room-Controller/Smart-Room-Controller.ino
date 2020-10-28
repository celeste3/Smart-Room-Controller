/*
 * Project: Midterm Smart Room Controller
 * Description: Massage therapy smart room settings
 * Author: Celeste Corazon
 * Date: October 26, 2020
 */

#include <SPI.h>
#include <Wire.h>

#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Ethernet.h>
#include <mac.h>
#include <wemo.h>

#include <OneButton.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_BME280 bme; // use I2C interface       Errors without this code
int bmeStatus;
float tempF;
float tempC;

EthernetClient client;
bool etherStatus;
const int serialClock = 10;

const int echoPin = 2;  // attach digital pin Echo of HC-SR04
const int trigPin = 3;  // attach digital pin Trig of HC-SR04

OneButton teaButton (15, false, false);
OneButton fanButton (16, false, false);

// Declare Variables for getMotion
long duration;  // variable for the duration of sound wave travel
int distance;   // variable for the distance measurement

void setup() {
  //Open Serial Communication and wait for port to open: //This Code is not mine testing Ethernet connection
  Serial.begin(9600);
  
  while (!Serial);
  Serial.println("Starting Program");
  //Start ethernet connection
  etherStatus = Ethernet.begin(mac); 
  if (!etherStatus) {
    Serial.println("failed to configure Ethernet using DHCP");
    //no point in continuing
    while(1);
    }
  //print your local IP address
  Serial.print("My IP address:");
  for (byte thisbyte = 0; thisbyte < 4; thisbyte++) {
    //print value of each byte of the IP address
    Serial.print(Ethernet.localIP()[thisbyte], DEC);
    if (thisbyte < 3) Serial.print(".");
    }
  Serial.println();
  
 //default settings
  bmeStatus = bme.begin(0x76);
  
  if(bmeStatus==false){
     Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
     Serial.print(F("Fail"));
  }
      // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds
         
  // Clear the buffer
  display.clearDisplay();

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);

  //From Brains HC-SR04 Test Code
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  
  Serial.begin(9600);
  delay(100);         // wait for Serial Monitor to Open 
  Serial.println("Ultrasonic Sensor HC-SR04 Test");

  teaButton.attachClick(clickTea);
  fanButton.attachClick(clickFan);
    
}

void loop() {
  displayTemp();
  getMotion();
  teaButton.tick();
  fanButton.tick();
  
} //End Void Loop

void getMotion(){
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds, this is the pulse that will be detected
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  distance = (duration * 0.034 / 2)*0.393701; // Speed of sound wave divided by 2 (go and back)
  Serial.printf("Time %i, Distance: %i, Duration %i \n",millis(),distance, duration);
}

void displayTemp() {
   // Reads temperature in fahrenheit
   tempC = bme.readTemperature();
   tempF = ( tempC*9/5)+32;
   
   display.clearDisplay();
   display.setTextSize(1);
   display.setTextColor(SSD1306_WHITE);
   display.setCursor(30,30); // Start at top-left corner

   Serial.printf("%f\n",tempF);
   display.printf("%f\n",tempF);
   display.display();  
}

void clickTea(){
  Serial.println("Tea was clicked");
  
}

void clickFan(){
  Serial.println("Fan was clicked");
}
