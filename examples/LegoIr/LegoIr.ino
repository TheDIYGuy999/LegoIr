// This example was cuccessfully tested on an Sparkfun Pro Micro in 8MHz & 16MHz version

//
// =======================================================================================================
// INCLUDE LIRBARIES & TABS
// =======================================================================================================
//
#include <LegoIr.h>

//
// =======================================================================================================
// CREATE OBJECTS
// =======================================================================================================
//

LegoIr pf;

//
// =======================================================================================================
// MAIN ARDUINO SETUP (1x during startup)
// =======================================================================================================
//
void setup() {
  pf.begin(3, 0);  // IR LED pin 3, channel 0 - 3 (in order to change the channel, just execute this line again)
}

//
// =======================================================================================================
// MAIN LOOP
// =======================================================================================================
//

void loop() {
  transmitLegoIr(); // Transmit Lego IR data
}

//
// =======================================================================================================
// TRANSMIT LEGO POWERFUNCTIONS IR SIGNAL
// =======================================================================================================
//

void transmitLegoIr() {
  static byte speedOld[2];
  static byte speed[2];
  static byte pwm[2];
  static unsigned long previousMillis;

  unsigned long currentMillis = millis();

  // read joystick positions into an array-----
  speed[0] = map(analogRead(A0), 0, 1023, 0, 100);
  speed[1] = map(analogRead(A1), 0, 1023, 0, 100);

  // compute pwm value for "red" and "blue" motor, if speed has changed more than +/- 3, or every 0.6s
  // NOTE: one IR pulse at least every 1.2 s is required in order to prevent the vehivle from stopping
  // due to a signal timeout!
  for (int i = 0; i <= 1; i++) {
    if ((speedOld[i] - 3) > speed[i] || (speedOld[i] + 3) < speed[i] || currentMillis - previousMillis >= 600) {
      speedOld[i] = speed[i];
      previousMillis = currentMillis;
      if (speed[i] >= 0 && speed[i] < 6) pwm[i] = PWM_REV7;
      else if (speed[i] >= 6 && speed[i] < 12) pwm[i] = PWM_REV6;
      else if (speed[i] >= 12 && speed[i] < 18) pwm[i] = PWM_REV5;
      else if (speed[i] >= 18 && speed[i] < 24) pwm[i] = PWM_REV4;
      else if (speed[i] >= 24 && speed[i] < 30) pwm[i] = PWM_REV3;
      else if (speed[i] >= 30 && speed[i] < 36) pwm[i] = PWM_REV2;
      else if (speed[i] >= 36 && speed[i] < 42) pwm[i] = PWM_REV1;
      else if (speed[i] >= 42 && speed[i] < 58) pwm[i] = PWM_BRK;
      else if (speed[i] >= 58 && speed[i] < 64) pwm[i] = PWM_FWD1;
      else if (speed[i] >= 64 && speed[i] < 70) pwm[i] = PWM_FWD2;
      else if (speed[i] >= 70 && speed[i] < 76) pwm[i] = PWM_FWD3;
      else if (speed[i] >= 76 && speed[i] < 82) pwm[i] = PWM_FWD4;
      else if (speed[i] >= 82 && speed[i] < 88) pwm[i] = PWM_FWD5;
      else if (speed[i] >= 88 && speed[i] < 94) pwm[i] = PWM_FWD6;
      else if (speed[i] >= 94) pwm[i] = PWM_FWD7;

      // then transmit IR data
      pf.combo_pwm(pwm[1], pwm[0]); // red and blue in one IR package
      //pf.single_pwm(RED, pwm[0]); // or each color separately
      //pf.single_pwm(BLUE, pwm[1]);
    }
  }
}
