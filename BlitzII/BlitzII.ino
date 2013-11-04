  /*
  Blitzsteuerung für ATTINY84
  https://github.com/damellis/attiny
  
  
  Anschluss:
    D0 = Taster
  
  
  PINs:
  
                    +-\/-+
   Ain0 (D 5) PB5  1|    |8  Vcc
   Ain3 (D 3) PB3  2|    |7  PB2 (D 2)  Ain1
   Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1
              GND  4|    |5  PB0 (D 0) pwm0
                    +----+

 */

#define PIN_TRIGGER  0
#define PIN_KEY      1
#define PIN_OUT      2
#define PIN_LED      4

#define OUT_ON       LOW
#define OUT_OFF      HIGH
#define LED_ON       LOW
#define LED_OFF      HIGH
#define TRIGGER_START   FALLING

#include <PinChangeInterrupt.h> 
#include <avr/sleep.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

void setup() {                
  // initialize the digital pin as an output.
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LED_ON);
  pinMode(PIN_OUT, OUTPUT);
  digitalWrite(PIN_OUT, OUT_OFF);
  
  // Eingang mit Pull-UP
  pinMode(PIN_TRIGGER, INPUT_PULLUP);
  pinMode(PIN_KEY, INPUT_PULLUP);
  
  // Initialize pin change interrupt
 attachPcInterrupt(PIN_TRIGGER,trigger_start,TRIGGER_START);
 attachPcInterrupt(PIN_KEY    ,key_start    ,FALLING);

  delay(500);
  digitalWrite(PIN_LED, LED_OFF);
}

void loop() {
  // sleep until pin change interrupt
  system_sleep();
}

void trigger_start()
{
}

void key_start()
{
}

// From http://interface.khm.de/index.php/lab/experiments/sleep_watchdog_battery/
void system_sleep() {
  cbi(ADCSRA,ADEN); // Switch Analog to Digital converter OFF
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Set sleep mode
  sleep_mode(); // System sleeps here
  sbi(ADCSRA,ADEN);  // Switch Analog to Digital converter ON
}

