
/* ============================================================
 *  Includes
 * ============================================================*/
#include "app.h"
#include "input.h"
#include "output.h"
#include <stdio.h>

/* ============================================================
 *  Defines
 * ============================================================*/
#define dLIMIT_COUNTER 3 

/* ============================================================
 *  Static (private) variables
 * ============================================================*/
unsigned char counter = 0;
/* ============================================================
 *  Static (private) functions
 * ============================================================*/
static void app_ConfigLed();
/* ============================================================
 *  Public functions
 * ============================================================*/
void app_Periodic() {

    if(input_GetRise(eBUTTON_1)) {
        if(++counter > dLIMIT_COUNTER) {
            counter = 0;
        }
        printf("COUNTER: %d\n", counter);
    }

    app_ConfigLed();

}
/* ============================================================
 *  Private functions (static)
 * ============================================================*/
static void app_ConfigLed() {
    
    static bool blink = 0;
    static unsigned short timeCounter = 0;

    switch(counter)
    {
        case 0:
            output_SetValue(eLED_YELLOW, 0);
        break;
        
        case 1:
            output_SetValue(eLED_YELLOW, 1);
        break;
        
        case 2:
            output_SetValue(eLED_YELLOW, blink);
            blink ^= 1;
        break;

        case 3:
            timeCounter++;
            if(timeCounter < 15)
            {
                output_SetValue(eLED_YELLOW, 1);
            }
            else if(timeCounter > 22)
            {
                timeCounter = 0;
            }
            else
            {
                output_SetValue(eLED_YELLOW, 0);
            }
        break;

        default:
        break;
    }
}