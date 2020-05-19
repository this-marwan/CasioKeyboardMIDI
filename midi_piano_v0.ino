#include <SoftwareSerial.h> //for debugging
SoftwareSerial mySerial(A0, A1); // RX, TX

void setup() {
  // put your setup code here, to run once:
  Serial.begin(31250);
  pinMode(13, INPUT);
  pinMode(12, INPUT);
  pinMode(11, INPUT);
  pinMode(10, INPUT);
  pinMode(9, INPUT);
  pinMode(8, INPUT);
  pinMode(7, INPUT);
  pinMode(6, INPUT);
  pinMode(5, INPUT);
  pinMode(4, INPUT);
  pinMode(3, INPUT);
  pinMode(2, INPUT);

  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
  mySerial.println("Hello, world?");

}

int state [38] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //array to hold our  button states

void loop() {
     /////////////////////////////Fourth SECTION////////////////////////////
   checkState(state,30,B00000100,B10000000,82); //D6 -
   checkState(state,31,B00000100,B01000000, 81); //D5 -
   checkState(state,32,B00000100,B00100000, 80); //D4 
   checkState(state,33,B00000100,B00010000, 79); //D3 - right note
   checkState(state,34,B00000100,B00001000, 78); //D2 -
   checkState(state,35,B00000100,B00000100, 77); //D1 -
   
   checkState1(state,36,B00000100,B00000010, 84); //D8    checkState1(state,36,B00000100,B00000010, 84); // gives the best result but mixes with it C8
   checkState1(state,37,B00000100,B00000001, 83); //D7    checkState1(state,37,B00000100,B00000001, 83); // gives the best result but mixes with it C7
   
   /////////////////////////////Third SECTION////////////////////////////
   checkState(state,20,B00001000,B10000000, 74); //C6
   checkState(state,21,B00001000,B01000000, 73); //C5
   checkState(state,22,B00001000,B00100000, 72); //C4
   checkState(state,23,B00001000,B00010000, 71); //C3
   checkState(state,24,B00001000,B00001000, 70); //C2
   checkState(state,25,B00001000,B00000100, 69); //C1

   checkState1(state,26,B00001000,B00000010, 76); //C8
   checkState1(state,27,B00001000,B00000001, 75); //C7

   /////////////////////////////SECOND SECTION////////////////////////////
   checkState(state,10,B00010000,B10000000, 66); //B6
   checkState(state,11,B00010000,B01000000, 65); //B5
   checkState(state,12,B00010000,B00100000, 64); //B4
   checkState(state,13,B00010000,B00010000, 63); //B3
   checkState(state,14,B00010000,B00001000, 62); //B2
   checkState(state,15,B00010000,B00000100, 61); //B1

   checkState1(state,16,B00010000,B00000010, 68); //B8
   checkState1(state,17,B00010000,B00000001, 67); //B7
   
  /////////////////////////////FIRST SECTION////////////////////////////
   checkState(state,1,B00100000,B10000000, 58); //A6
   checkState(state,2,B00100000,B01000000, 57); //A5
   checkState(state,3,B00100000,B00100000, 56); //A4
   checkState(state,4,B00100000,B00010000, 55); //A3
   checkState(state,5,B00100000,B00001000, 54); //A2
   checkState(state,6,B00100000,B00000100, 53); //A1

   checkState1(state,7,B00100000,B00000010, 60); //A8
   checkState1(state,8,B00100000,B00000001, 59); //A7

   

  
}

void checkState(int state[] ,int i, byte section, byte pin,byte note)
{
      //A conatins the button states
      //i is the number of the button, used for indexing A
      //section identifies the state of the upper 4 bits that dictate which section of the keyboard is active
      //pin is the pin reponsible for reading this key 
      if ((PINB & B00111100) ==  section ) {
      if ((PIND & pin) ==  pin) //if our section is active and our pin is active
      {
        //button i is pressed
        state[i]++;
        if (state[i] == 4) //the button has been pressed two iterations in a row
        {
//           mySerial.print(i);
//           mySerial.println(" ON");
          noteOn(0x090,note,0x45);
          }
      }
      else if (state[i] != 0) //not pressed now and was pressed previously
      {
        if (state[i] >= 4) //the button has been considered ON
        {
//           mySerial.print(i);
//           mySerial.println(" OFF");
           noteOn(0x090,note,0x00);
          }
        state[i] = 0;
      }
  }
}

void checkState1(int state[] ,int i, byte section, byte pin, byte note)
{
      //Identical to the first but just for pin 8 & 9 since they are on Port B rather than D
      if ((PINB & B00111100) ==  section ) {
      if ((PINB & pin) ==  pin) //if our section is active and our pin is active
      {
        //button i is pressed
        state[i]++;
        if (state[i] == 4) //the button has been pressed two iterations in a row
        {
//           mySerial.print(i);
//           mySerial.println(" ON");
           noteOn(0x090,note,0x45);
          }
      }
      else if (state[i] != 0) //not pressed now and was pressed previously
      {
        if (state[i] >= 4) //the button has been considered ON
        {
//           mySerial.print(i);
//           mySerial.println(" OFF");
           noteOn(0x090,note,0x00);
          }
        state[i] = 0;
      }
  }
}
// plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that
// data values are less than 127:
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}
