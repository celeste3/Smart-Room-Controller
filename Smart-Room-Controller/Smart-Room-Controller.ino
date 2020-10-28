/*
 * Project: Midterm Smart Room Controller
 * Description: Massage therapy smart room settings
 * Author: Celeste Corazon
 * Date: October 26, 2020
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Ethernet.h>
#include <mac.h>
#include <wemo.h>

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

const int echoPin = 3;  // attach digital pin Echo of HC-SR04
const int trigPin = 4;  // attach digital pin Trig of HC-SR04

const int teaButton = 13;
const int fanButton = 14;

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

      pinMode (teaButton, INPUT);
      pinMode (fanButton, INPUT);
  }
}

//
//
//// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
//  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
//    Serial.println(F("SSD1306 allocation failed"));
//    for(;;); // Don't proceed, loop forever
//  }
//               //CODE FOR OLED
//  // Show initial display buffer contents on the screen --
//  // the library initializes this with an Adafruit splash screen.
//  display.display();
//  delay(2000); // Pause for 2 seconds
//
//  // Clear the buffer
//  display.clearDisplay();
//
//  // Draw a single pixel in white
//  display.drawPixel(10, 10, SSD1306_WHITE);
//
//  // Show the display buffer on the screen. You MUST call display() after
//  // drawing commands to make them visible on screen!
//  display.display();
//  delay(2000);
//  // display.display() is NOT necessary after every single drawing command,
//  // unless that's what you want...rather, you can batch up a bunch of
//  // drawing operations and then update the screen all at once by calling
//  // display.display(). These examples demonstrate both approaches...
//  
//   testdrawstyles();    // Draw 'stylized' characters THIS IS NEEDED

void loop() {
   // Reads temperature in fahrenheit
   tempC = bme.readTemperature();
   tempF = ( tempC*9/5)+32;
   Serial.printf("%f\n",tempF);
} //End Void Loop
