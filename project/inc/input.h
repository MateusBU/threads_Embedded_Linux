#ifndef INPUT_H
#define INPUT_H

/* ============================================================
 *  Includes
 * ============================================================*/

#include <gpiod.h>
/* ============================================================
 *  Defines / Macros
 * ============================================================*/

/* ============================================================
 *  Typedefs / Enums / Structs
 * ============================================================*/

typedef enum {
    eBUTTON_1,
    eNUMBER_OF_INPUTS,
} inputsName_t;

/* ============================================================
 *  Extern Variables
 * ============================================================*/


/* ============================================================
 *  Function Prototypes
 * ============================================================*/
void input_Init(struct gpiod_chip *chip);
void input_RequestRelease();
int input_GetValue(inputsName_t input);
void input_Periodic();
bool input_GetRise(inputsName_t input);
bool input_GetFall(inputsName_t input);

#endif /* INPUT_H */
