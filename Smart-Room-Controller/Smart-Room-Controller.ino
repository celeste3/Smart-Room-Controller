/*
 * Project: Midterm Smart Room Controller
 * Description: Massage therapy smart room settings
 * Author: Celeste Corazon
 * Date: October 26, 2020
 */

#include <SPI.h>
#include <Ethernet.h>
#include <mac.h>

EthernetClient client;
const int

void setup() {
  //Open Serial Communication and wait for port to open: //This Code is not mine testing Ethernet connection
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Starting Program");
  //Start ethernet connection
  status = Ethernet.begin(mac); 
  if (!status) {
    Serial.println("failed to configure Ethernet using DHCP");
    //no point in continueing 
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
}


}

void loop() {
  
  // put your main code here, to run repeatedly:

}
