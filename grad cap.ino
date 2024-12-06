// cpsc 599 A3 
// maham fatima 
// thursday december 5

// this code is for a grad hat which uses sound to map to led light strip and a photo interupter to map music playing on a speaker and a motor fan activating a floating effect for glitter/foam beads

// code sources: 
// sound sensor 
// https://arduinomodules.info/ky-037-high-sensitivity-sound-detection-module/
// ​
// dc motor 
// ​https://medium.com/@arduinounomagic/how-to-operate-dc-motor-using-arduino-ab5772541b7f
// ​
// speaker 
// https://www.hackster.io/blackpanda856/play-music-using-arduino-uno-and-a-speaker-b94e4a
// ​
// photo interrupter 
// https://maker.pro/arduino/projects/arduino-photo-interrupter-module
// ​
// audio tone library for song
// https://github.com/robsoncouto/arduino-songs/blob/master/nevergonnagiveyouup/nevergonnagiveyouup.ino
// ​
// fast led library 
// https://github.com/FastLED/FastLED
// ​https://www.instructables.com/Basic-of-FastLED/
#include <FastLED.h>

/*
  Never Gonna Give You Up
  Connect a piezo buzzer or speaker to pin 4 or select a new pin.
  More songs available at https://github.com/robsoncouto/arduino-songs

  Robson Couto, 2019
  Source: https://github.com/robsoncouto/arduino-songs/blob/master/nevergonnagiveyouup/nevergonnagiveyouup.ino
*/
// pin defintions 
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0
// end code 


// Pin Definitions  
#define SOUND_PIN  8        // Microphone (Sound Sensor) pin digital
#define SOUND_PIN  A0       // Microphone (Sound Sensor) pin analog 
#define MOTOR_PIN 3         // Motor  pin

#define SPEAKER_PIN 4       // Speaker pin
#define PHOTO_PIN  6        // Photo interrupter pin
#define LED_PIN     7       // LED strip pin
#define NUM_LEDS    60      // Number of LEDs in the strip

bool isSongPlaying = false;  // Flag to track whether the song is playing
bool isMotorRunning = false;  // Flag to track whether the motor is running

CRGB leds[NUM_LEDS];       // Array to hold LED data

//Source: https://github.com/robsoncouto/arduino-songs/blob/master/nevergonnagiveyouup/nevergonnagiveyouup.ino

int tempo = 114;          // from source for never gonna give u 

int melody[] = {

  // Never Gonna Give You Up - Rick Astley
  // Score available at https://musescore.com/chlorondria_5/never-gonna-give-you-up_alto-sax
  // Arranged by Chlorondria

  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,4, //1
  NOTE_E5,-4, NOTE_FS5,-4, NOTE_A5,16, NOTE_G5,16, NOTE_FS5,8,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,2,
  NOTE_A4,16, NOTE_A4,16, NOTE_B4,16, NOTE_D5,8, NOTE_D5,16,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,4, //repeat from 1
  NOTE_E5,-4, NOTE_FS5,-4, NOTE_A5,16, NOTE_G5,16, NOTE_FS5,8,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,2,
  NOTE_A4,16, NOTE_A4,16, NOTE_B4,16, NOTE_D5,8, NOTE_D5,16,
  REST,4, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_D5,8, NOTE_E5,8, NOTE_CS5,-8,
  NOTE_B4,16, NOTE_A4,2, REST,4, 

  REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,4, NOTE_A4,8, //7
  NOTE_A5,8, REST,8, NOTE_A5,8, NOTE_E5,-4, REST,4, 
  NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_D5,8, NOTE_E5,8, REST,8,
  REST,8, NOTE_CS5,8, NOTE_B4,8, NOTE_A4,-4, REST,4,
  REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,4,
  NOTE_E5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4, REST,4,
   
  NOTE_D5,2, NOTE_E5,8, NOTE_FS5,8, NOTE_D5,8, //13
  NOTE_E5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4, NOTE_A4,4,
  REST,2, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8,
  REST,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,

  NOTE_E5,-8, NOTE_E5,-8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,-8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //18
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,8, NOTE_A4,8, NOTE_A4,8, 
  NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16//,
  // i played a short version but below is the full song
  // NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,  //23
  // NOTE_E5,4, NOTE_D5,2, REST,4,
  // REST,8, NOTE_B4,8, NOTE_D5,8, NOTE_B4,8, NOTE_D5,8, NOTE_E5,4, REST,8,
  // REST,8, NOTE_CS5,8, NOTE_B4,8, NOTE_A4,-4, REST,4,
  // REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,4,
  // REST,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8, NOTE_D5,8,
  
  // REST,8, NOTE_A4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, //29
  // REST,8, NOTE_CS5,8, NOTE_B4,8, NOTE_A4,-4, REST,4,
  // NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,4, REST,8,
  // REST,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,4, NOTE_E5,-4, 
  // NOTE_D5,2, NOTE_D5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4, 
  // NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8, NOTE_A4,8, NOTE_A4,4,

  // REST,-4, NOTE_A4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, //35
  // REST,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  // NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  // NOTE_E5,-8, NOTE_E5,-8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  // NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8, 

  //  NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //40
  // NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  // NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  // NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,  
  // NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
   
  // NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //45
  // NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  // NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,  
  // NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  // NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //45
  
  // NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  // NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8, 

  // NOTE_E5,4, NOTE_D5,2, REST,4
};


// Number of notes in the melody
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// Duration of a whole note in milliseconds
int wholenote = (60000 * 4) / tempo;
// end code


void setup() {
  
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);  // Initialize LED

  pinMode(PHOTO_PIN, INPUT);                              // photo interupter pin as input
  pinMode(SOUND_PIN, INPUT);                              // sound sensor pin as input
  pinMode(SPEAKER_PIN, OUTPUT);                           // speaker pin as output
  pinMode(MOTOR_PIN, OUTPUT);                             // Motor pin as output

  Serial.begin(9600);
}

void loop() {
  int soundValue = analogRead(SOUND_PIN);                 // Read microphone value
  int photoState = digitalRead(PHOTO_PIN);                // Read photo interrupter state


if (photoState == HIGH && !isSongPlaying && !isMotorRunning) {
    // code modified from https://maker.pro/arduino/projects/arduino-photo-interrupter-module

    playSong();                                           // Play song if photo resistor is activated
    isSongPlaying = false;                                // Reset flag 
    delay(200);                                           // Small delay 
    runMotor();                                           // After song, run the motor fan
    delay(100);                                           // Small delay 

  }
  
  if (soundValue > 50) {                                  // If the sound sensor detects loud sound (e.g., music), change LED color
  // code modified from https://arduinomodules.info/ky-037-high-sensitivity-sound-detection-module/
    setLEDColor(CRGB(0, 45, 0));                          // Green color for sound detection
  }else {
    setLEDColor(CRGB(45, 0, 0));                          // If no motion detected, set LED to red (the default state)
  }

  delay(100);                                             // delay
}

void playSong() {
   // Source for song: https://github.com/robsoncouto/arduino-songs/blob/master/nevergonnagiveyouup/nevergonnagiveyouup.ino
   // modified from https://www.hackster.io/blackpanda856/play-music-using-arduino-uno-and-a-speaker-b94e4a


  int divider = 0, noteDuration = 0;

  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    // Calculate duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; 
    }
 
    tone(SPEAKER_PIN, melody[thisNote], noteDuration * 0.9);     // Play the note
    delay(noteDuration);                                         // Wait for note duration

    noTone(SPEAKER_PIN);                                        // turn music off
  }
  isSongPlaying = true;                                         // Set song playing flag to true

  
}

// Function to run the motor for 10 seconds to blow the foam beads
void runMotor() {
  // code modified from ​https://medium.com/@arduinounomagic/how-to-operate-dc-motor-using-arduino-ab5772541b7f

  isMotorRunning = true;        // Set the flag to true indicating the motor is running
  digitalWrite(MOTOR_PIN, 240); // Turn on motor (fan) at 240 speed
  delay(10000);                 // Run the motor for 10 seconds
  digitalWrite(MOTOR_PIN, 0);   // Turn off motor (fan) after 10 seconds
  isMotorRunning = false;       // Reset the flag after the motor stops
}
// Function to set LED color
void setLEDColor(CRGB color) {
  // code modified from : ​https://www.instructables.com/Basic-of-FastLED/
  // i only needed ~30 leds so i set it to only have those lit up
  for (int i = 29; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
  FastLED.show();  // Update LED strip
}
