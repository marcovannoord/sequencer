// Arduino Nano sequencer
// By Marco van Noord
// Copyright (C) Van Noord Engineering - 2019

#include "Arduino.h"

// Amount of outputs - or steps - the system has
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
#define STEP9 A0
#define STEP10 A1
#define STEP11 A2
#define STEP12 A3
#define STEP13 A4
#define STEP14 A5
#define STEP15 13
#define STEP16 9 //0 // TX pin, since we won't use Serial input

// Put the pins in an array, so we can loop through them later on
const uint8_t stepPins[16] = {STEP1, STEP2, STEP3, STEP4, STEP5, STEP6, STEP7, STEP8, STEP9, STEP10, STEP11, STEP12, STEP13, STEP14, STEP15, STEP16};

// Pins used as inputs
#define RESET_PIN 10
#define REVERSE_PIN 11
#define CLOCK_PIN 12
// Unused pin: RX(1)

uint8_t forward_clock_level = LOW;
uint8_t previous_forward_clock_level = LOW;

uint8_t reset_level = LOW;
uint8_t previous_reset_level = LOW;

// keeps track on which output should be active at the moment.
// output "0" does not exist, meaning that no output will be active at that moment
uint8_t output_number = 0;
bool direction_forward = true; // Should we go forward? (or reverse)

void setup()
{

  // Warning: do not use Serial, since it prevents output STEP16 from working correctly
  // Set all step outputs to OUTPUT mode
  for (size_t i = 0; i < OUTPUT_STEPS; i++)
  {
    pinMode(stepPins[i], OUTPUT);
  }
  pinMode(CLOCK_PIN, INPUT);
  pinMode(RESET_PIN, INPUT);
  pinMode(REVERSE_PIN, INPUT);
  Serial.begin(9600);
  Serial.println("started Synth");
}

void loop()
{
  if (Serial.available())
  {
    if (Serial.read() == 'c')
    {
      Serial.println("keyboardClock");
      if (direction_forward) // if we go forwards
      {                      // Then step forward and check if we are within bounds
        if (++output_number > OUTPUT_STEPS)
        {
          output_number = 1; // and reset back to the start when we arent't
        }
        Serial.println("forward  " + String(output_number));
      }
      else // else we are going backwards
      {
        if (--output_number < 1) // Then check if we arrived at the start of the sequence
        {
          output_number = OUTPUT_STEPS; // If so, reset to the end of the sequence
        }
        Serial.println("reverse  " + String(output_number));
      }
      
    }
  }
  direction_forward = digitalRead(REVERSE_PIN); // Read and set the direction from the switch

  // If the forward clock has been changed (level is high)
  forward_clock_level = digitalRead(CLOCK_PIN);
  // Serial.println(digitalRead(CLOCK_PIN));
  if ((forward_clock_level == HIGH) && (previous_forward_clock_level == LOW))
  {
    Serial.println("clock");

    if (direction_forward) // if we go forwards
    {                      // Then step forward and check if we are within bounds
      if (++output_number > OUTPUT_STEPS)
      {
        output_number = 1; // and reset back to the start when we arent't
      }
    }
    else // else we are going backwards
    {
      if (--output_number < 1) // Then check if we arrived at the start of the sequence
      {
        output_number = OUTPUT_STEPS; // If so, reset to the end of the sequence
      }
    }
    Serial.println("enable " + String(output_number));
  }
  previous_forward_clock_level = forward_clock_level; // store the state

  // Reset logic: when high, start aat the first step output.
  reset_level = digitalRead(RESET_PIN);
  if ((reset_level == HIGH) && (previous_reset_level == LOW))
  {
    Serial.println("reset");
    output_number = 1;
  }
  previous_reset_level = reset_level; // store the state

  // Now enable the correct output
  enable_single_output(output_number);
}
void enable_single_output(uint8_t output)
{

  for (size_t i = 1; i <= OUTPUT_STEPS; i++) // loop from 1 through 16 (steps)
  {
    if (i == output)
    {
      digitalWrite(stepPins[i - 1], HIGH); // i-1 since the array is zero-based
    }
    else
    {
      digitalWrite(stepPins[i - 1], LOW);
    }
  }
}