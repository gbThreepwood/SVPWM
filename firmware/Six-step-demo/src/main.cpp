/*
 * Slow six step output demonstration.
 * 
 * Eirik Haustveit, 2020.
 * 
 * 
 * Step through the six unique active vectors of a
 * three phase two level inverter.
 * 
 * The correct step sequence for counter-clockwise 
 * rotation is the follwing:
 * 
 * 000  0
 * 001  1
 * 011  3
 * 010  2
 * 110  6
 * 100  4
 * 101  5
 * 111  7
 * 
 * This is almost like Gray code.
 * 
 * 
 */

#include <Arduino.h>

const uint8_t phase_a = 9;
const uint8_t phase_b = 10;
const uint8_t phase_c = 11;

const uint8_t toggle_button = 12;

const uint8_t ccw_sequence[8] = {0x00, 0x01, 0x03, 0x02, 0x06, 0x04, 0x05, 0x07};

#define CORRECT_PUSH_BUTTON_STEP

uint8_t toggle_button_detected();


uint8_t i = 0;


void setup() {

  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);

  Serial.begin(9600);

}

void loop() {

#ifdef STEP_LOOP

  for(uint8_t i = 0; i <= 7; i++){

    digitalWrite(phase_a, i & 0x01);
    digitalWrite(phase_b, (i >> 1) & 0x01);
    digitalWrite(phase_c, (i >> 2) & 0x01);

    Serial.print("Config: ");
    Serial.print(i, BIN);
    Serial.println();

    delay(1000);
  }
#endif

#ifdef PUSH_BUTTON_STEP

  if(toggle_button_detected()){
    

    digitalWrite(phase_a, i & 0x01);
    digitalWrite(phase_b, (i >> 1) & 0x01);
    digitalWrite(phase_c, (i >> 2) & 0x01);

    Serial.print("Config: ");
    Serial.print(i, BIN);
    Serial.println();

    i++;

    if(i > 7)
      i = 0;
  }

#endif

#ifdef CORRECT_PUSH_BUTTON_STEP

  if(toggle_button_detected()){
    
    digitalWrite(phase_a, ccw_sequence[i] & 0x01);
    digitalWrite(phase_b, (ccw_sequence[i] >> 1) & 0x01);
    digitalWrite(phase_c, (ccw_sequence[i] >> 2) & 0x01);

    Serial.print("Config: ");
    Serial.print(ccw_sequence[i], BIN);
    Serial.println();

    i++;

    if(i > 7)
      i = 0;
  }

#endif

}

uint8_t toggle_button_detected(){

  static uint16_t shift_register = 0;
  static uint32_t old_millis = 0;

  if(millis() > old_millis + 5){

    old_millis = millis();

    uint8_t input_state = digitalRead(toggle_button);

    shift_register = (shift_register << 1) | input_state | 0xC000;

    if(shift_register == 0xE000){
      Serial.print("Toggle event detected.");
      return 1;
    }
  }
  return 0;
}