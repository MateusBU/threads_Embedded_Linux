
/* ============================================================
 *  Includes
 * ============================================================*/
#include "app.h"
#include "input.h"
#include "output.h"

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

    if(input_GetValue(eBUTTON_1)) {
        if(++counter > dLIMIT_COUNTER) {
            counter = 0;
        }
    }

    app_ConfigLed();

}
/* ============================================================
 *  Private functions (static)
 * ============================================================*/
static void app_ConfigLed() {

    static int blink = 0;
    static int timeCounter = 0;

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
            else if(timeCounter < 22)
            {
                timeCounter = 0;
                output_SetValue(eLED_YELLOW, 0);
            }
        break;

        default:
        break;
    }
}