//LOOK MUM NO COMPUTER KEYBOARD SEQUENCER. A SIMPLE DESIGN TO MAKE A 4017 STYLE SEQUENCER WITH MORE ADDED FUNCTIONS.
//MORE INFO CHECK LOOKMUMNOCOMPUTER.COM
//PLEASE EMAIL ME COMPUTER@LOOKMUMNOCOMPUTER.COM OR LOOKMUMNOCOMPUTER@GMAIL.COM IF ANY QUESTIONS
//ANY MODIFICATIONS PLEASE LET ME KNOW AND I CAN FEATURE ON THE WEBSITE
//OPEN SOURCE. DONT USE IN A PRODUCT OR WHATEVER WITHOUT TALKING TO ME
//SAM BATTLE 2017
//BOOM

//ALSO TO ADD! I HAVE MADE THIS CODE IN A WAY ITS EASY TO UNDERSTAND FOR A NONE CODER (LIKE MYSELF)
//I REMEMBER WHEN I STARTED ON ARDUINO BEING LIKE WHAT THE HELL IS GOING ON.
//SO IVE LAYED IT OUT LOGICALLY, SEINSE IT ISNT A COMPLICATED PROGRAM I FIGURED WHY THE HECK NOT!

//SO YES THIS ISNT THE BEST WAY OF GOING ABOUT THIS HOWEVER IT IS THE EASIEST TO UNDERSTAND
//FOR A NONE CODER MIND.

#include "Arduino.h"
const uint8_t OUTPUT_STEPS{16};
// Below, define the pin outputs that we use for each step.
#define STEP1 2
#define STEP2 3
#define STEP3 4
#define STEP4 5
#define STEP5 6
#define STEP6 7
#define STEP7 8
#define STEP8 9
#define STEP9 14
#define STEP10 15
#define STEP11 16
#define STEP12 17
#define STEP13 18
#define STEP14 19
#define STEP15 21
#define STEP16 20
const uint8_t stepPins[16] = {STEP1, STEP2, STEP3, STEP4, STEP5, STEP6, STEP7, STEP8, STEP9, STEP10, STEP11, STEP12,STEP13, STEP14, STEP15, STEP16}

#define FORWARD_CLOCK_PIN  12
#define RESET 10

//ABOVE BASICALLY DEFINES THE NAMES OF THE PINS, PLEASE REMEMBER THE ANALOG PINS A0,A1,A2, BLAH BLAH CAN BE USED AS DIGITAL PINS. THE ARE
//DIGITAL 14 and UP!

int val = 0;
int old_val = 0;
int val1 = 0;
int old_val1 = 0;
int val2 = 0;
int old_val2 = 0;
int val3 = 0;
int old_val3 = 0;
int val4 = 0;
int old_val4 = 0;

int vals1 = 0;
int old_vals1 = 0;
int vals2 = 0;
int old_vals2 = 0;
int vals3 = 0;
int old_vals3 = 0;
int vals4 = 0;
int old_vals4 = 0;
int vals5 = 0;
int old_vals5 = 0;
int vals6 = 0;
int old_vals6 = 0;
int vals7 = 0;
int old_vals7 = 0;
int vals8 = 0;
int old_vals8 = 0;

int state = 0;
int led = 17;
int newled = 1;

void setup()
{
  // Set all step outputs to OUTPUT mode
  for (size_t i = 0; i < OUTPUT_STEPS; i++)
  {
    pinMode(stepPins[i], OUTPUT);
  }
  pinMode(FORWARD_CLOCK_PIN, INPUT);
  // pinMode(BACK, INPUT);
  pinMode(RESET, INPUT);
  // pinMode(ZERO, INPUT);

  //SET THE PINS TO IN OR OUT
}

void loop()
{
  // If the forward clock has been changed
  forward_clock_level = digitalRead(FORWARD_CLOCK);
  if ((forward_clock_level == HIGH) && (previous_forward_clock_level == LOW))
  {
    newled = led - 1;
    if (newled <= 8)
    {
      newled = 16;
    }
    led = newled;
  }

  //THIS IS THE THING THAT MAKES IT GO FORWARD_CLOCK, IT SAYS -1 YOULL SEE ALL OF THE NUMBERS AND WHAT THEY DO BELOW

  val2 = digitalRead(ZERO);
  if ((val2 == HIGH) && (old_val2 == LOW))

  {
    newled = led = 17;
    led = newled;
  }

  //THIS MAKES THE ZERO COMMAND WORK. 17 IS WHEN NO LIGHTS ARE ON

  val3 = digitalRead(RESET);
  if ((val3 == HIGH) && (old_val3 == LOW))

  {
    newled = led = 16;
    led = newled;
  }

  //RESET BACK TO STEP 1

  val4 = digitalRead(BACK);
  if ((val4 == HIGH) && (old_val4 == LOW))

  {
    newled = led + 1;
    if (newled >= 17)
    {
      newled = 9;
    }
    led = newled;
  }

  //GO BACKWARDS

  //BELOW ARE ALL OF THE STEP BUTTONS AND WHAT THEY DO. BASICALLY WHEN THEY ARE HIT THE LED NUMBER GOES TO THE RIGHT NUMBER

  old_val = val;
  old_val1 = val1;
  old_val2 = val2;
  old_val3 = val3;
  old_val4 = val4;

  if (newled >= 17)
  {
    newled = 9;
  }
  if (newled <= 8)
  {
    newled = 16;
  }
}
