//
// Lego Power Functions Infrared Control for Arduino
// see http://www.philohome.com/pf/LEGO_Power_Functions_RC_v120.pdf for more info
// Based on SuperCow's code (http://forum.arduino.cc/index.php?topic=38142.0)
// And Jurriaans library https://github.com/jurriaan/Arduino-PowerFunctions
//
// Modified and enhanced by TheDIYGuy999, June 2016:
// - Begin function added to allow channel switching during runtime
// - Modifications to make it also compatible with 8MHz Arduino versions

// Modified and enhanced by TheDIYGuy999, December 2017:
// - Library V1.11 is now compatible with CPU's faster than 16MHz. Tested on an STM32 ARM "Maple" board

#ifndef LegoIr_h
#define LegoIr_h

#include <stdio.h>
#include "Arduino.h"

#define COMBO_DIRECT_MODE 0x01
#define SINGLE_PIN_CONTINUOUS 0x2
#define SINGLE_PIN_TIMEOUT 0x3
#define SINGLE_OUTPUT 0x4
#define SINGLE_EXT 0x6
#define ESCAPE 0x4

#define IR_CYCLES(num) (uint16_t) ((1.0/38000.0) * 1000 * 1000 * num) // 26.315

#define START_STOP IR_CYCLES(39) // 39
#define HIGH_PAUSE IR_CYCLES(21) // 21
#define LOW_PAUSE IR_CYCLES(10) // 10
/*
 #if F_CPU == 8000000 // 8MHz CPU
 #define HALF_PERIOD IR_CYCLES(0.5) //optimal signal strength with 0.5
 #endif*/

//#if F_CPU == 16000000 // 16MHz CPU
#define HALF_PERIOD IR_CYCLES(0.5) //optimal signal strength with 0.3  instead of 0.5
//#endif

#define MAX_MESSAGE_LENGTH IR_CYCLES(522) // 2 * 45 + 16 * 27 = 522

//PWM speed steps
#define PWM_FLT 0x0
#define PWM_FWD1 0x1
#define PWM_FWD2 0x2
#define PWM_FWD3 0x3
#define PWM_FWD4 0x4
#define PWM_FWD5 0x5
#define PWM_FWD6 0x6
#define PWM_FWD7 0x7
#define PWM_BRK 0x8
#define PWM_REV7 0x9
#define PWM_REV6 0xA
#define PWM_REV5 0xB
#define PWM_REV4 0xC
#define PWM_REV3 0xD
#define PWM_REV2 0xE
#define PWM_REV1 0xF


//output
#define RED 0x0
#define BLUE 0x1

class LegoIr
{
public:
    LegoIr();
    void begin(uint8_t, uint8_t);
    void single_pwm(uint8_t, uint8_t);
    void single_increment(uint8_t);
    void single_decrement(uint8_t);
    void red_pwm(uint8_t);
    void blue_pwm(uint8_t);
    void combo_pwm(uint8_t, uint8_t);
    
private:
    void pause(uint8_t);
    void send_bit();
    void send();
    void start_stop_bit();
    bool delayUnblocking (unsigned long);
    uint8_t _channel;
    uint8_t _pin;
    uint8_t _nib1, _nib2, _nib3;
    uint8_t _toggle;
};

#endif
// END OF FILE
