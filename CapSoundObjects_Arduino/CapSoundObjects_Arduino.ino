/**************************************************************************************
   Capacitive Touch Sound Objects by A Berkoy.

   Uses touch-triggered conductive materials for unconventional sound interface.
   (Create sensors from copper, aluminum foil, metal cutlery, food, conductive ink, etc.)
   Sends sensor data from Arduino over Serial to trigger sound files in Processing.

   This code is modiefied from Capacitive Touch Sense Materials Test Code, by Chris Taylor for SparkFun
   Download here: http://cdn.sparkfun.com/Homepage/CapSense_Materials.zip

   The code utilizes the CapacitiveSense library written by by Paul Badger.
   The example circuit, library description, and explanation can be found here:
   http://arduino.cc/playground/Main/CapacitiveSensor?from=Main.CapSense

   The connections of the individual circuits and their respective send/receive
   pins is as follows:

    Digital Pins 3 & 4 -- sensor1 send & receive
    Digital Pins 5 & 6 -- sensor2 send & receive
    Digital Pins 7 & 8 -- sensor3 send & receive
    Digital Pins 9 & 10 -- sensor4 send & receive
    Digital Pins 11 & 12 -- sensor5 send & receive

    Sendpin should be the pin connected directly to the resistor.
    Resistor value impacts sensor sensitivity. Try resistors in 50K- 50M range.
    (I am using 460K.)

    Digital Pin 13 -- LED indicator input pin

   This code initializes the CapSense pins, and then checks for a threshold level (100)
   of the arbitrary units returned by the CapacitiveSensor function. It toggles the
   LED when it detects a change and writes which sensor was touched to Serial.


**************************************************************************************/

#include <CapacitiveSensor.h>

#define LED 13

// INITIALIZE CAPSENSE PINS
// CapacitiveSensor(sendpin, recvpin)
CapacitiveSensor   sensor1 = CapacitiveSensor(3, 4);
CapacitiveSensor   sensor2 = CapacitiveSensor(5, 6);
CapacitiveSensor   sensor3 = CapacitiveSensor(7, 8);
CapacitiveSensor   sensor4 = CapacitiveSensor(9, 10);
CapacitiveSensor   sensor5 = CapacitiveSensor(11, 12);

void setup()
{
  // SET UP COMMUNICATIONS AND LED
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  // CALIBRATE CAPACITIVE SENSE PIN TIMING
  // Setting this value to 0xFFFFFFFF turns off autocalibrate (see library page)
  sensor1.set_CS_AutocaL_Millis(0xFFFFFFFF);
  sensor2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  sensor3.set_CS_AutocaL_Millis(0xFFFFFFFF);
  sensor4.set_CS_AutocaL_Millis(0xFFFFFFFF);
  sensor5.set_CS_AutocaL_Millis(0xFFFFFFFF);
}

void loop()
{
  // SAMPLE SENSOR CAPACITANCE
  // These functions sample the receive pins of the sensors 30 times. The largest
  // sample is subtracted from the smallest sample and returns the total. This
  // number is in arbitrary units.
  long total1 =  sensor1.capacitiveSensor(30);
  long total2 =  sensor2.capacitiveSensor(30);
  long total3 =  sensor3.capacitiveSensor(30);
  long total4 =  sensor4.capacitiveSensor(30);
  long total5 =  sensor5.capacitiveSensor(30);

  // CHECK THRESHOLD AND REACT
  // If the returned value is greater than set threshold, light the
  // LED and print which sensor was touched.
  //Modify threshold values to change sensitivity of sensor.
  if (total1 > 100) {
    Serial.write(1);
    digitalWrite(LED, HIGH);
  }
  else if (total2 > 100) {
    Serial.write(2);
    digitalWrite(LED, HIGH);
  }
  else if (total3 > 100) {
    Serial.write(3);
    digitalWrite(LED, HIGH);
  }
  else if (total4 > 100) {
    Serial.write(4);
    digitalWrite(LED, HIGH);
  }
  else if (total5 > 100) {
    Serial.write(5);
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }

  delay(10); // Delay so we don't print too fast

  //Monitor sensor values
  //Serial.println(total1);
  //Serial.println(total2);
  //Serial.println(total3);
}

