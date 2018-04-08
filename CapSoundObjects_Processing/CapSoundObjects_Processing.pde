/*
Capacitance demo by A Berkoy.
 Reads incoming values written to the serial port by Arduino
 and triggers sounds.
 
 Uses Minim Library. Install from Processing Contributed Libraries.
 Reference at http://code.compartmental.net/minim/ under AudioPlayer
 */

import processing.serial.*; //imports Serial library from Processing
import ddf.minim.*; //imports minim library from Processing


Serial myPort; // creates object from Serial class
Minim minim;  //creates object from Minim class
//creates objects to store audio files
//we will use the first object "track" to switch between the files to play
AudioPlayer track, cat, chime, fork, giggle, magic, magic_wand; 

int sensor; // creates variable for incoming data from serial, tracking which sensor

void setup() {
  /*
We must tell Processing which port to read from.
   Run the sketch and check your console 
   to see the results of printArray(Serial.list());
   and that is how you know the port to use.
   On my Mac, it is port 1 and so I open Serial.list()[1].
   */

  printArray(Serial.list()); // this line prints the port list to the console
  String portName = Serial.list()[1]; //change the number in the [] for the port you need
  myPort = new Serial(this, portName, 9600);

  minim = new Minim(this); // enables Minim to load files from the data directory
  //loads sound files from data directory
  cat= minim.loadFile("cat.mp3");
  chime= minim.loadFile("chime.mp3");
  fork= minim.loadFile("fork.mp3");
  giggle= minim.loadFile("giggle.mp3");
  magic= minim.loadFile("magic.mp3");
  magic_wand= minim.loadFile("magic_wand.mp3");
}

void draw() {
  if ( myPort.available() > 0) { // If data is available,
    sensor = myPort.read(); // read it and store it in sensor

    trackHandle(); //function for handling which track to play, see below
  }
  println (sensor); //prints to console
}

void trackHandle() { 
  //Assigns audio file to track in relation to sensor data
  if (sensor==1) {
    track= cat;
  } else if (sensor==2) {
    track= giggle;
  } else if (sensor==3) {
    track= magic;
  } else if (sensor==4) {
    track= chime;
  } else if (sensor==5) {
    track= magic_wand;
  }

  //play track one time if track is not already playing
  if (track.isPlaying()) {
    //do nothing
  } else {
    track.rewind();  //rewind it so it's cued up for playing
    track.play(); //play it
  }
}