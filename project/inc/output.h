#ifndef OUTPUT_H
#define OUTPUT_H

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
    eLED_YELLOW,
    eNUMBER_OF_OUTPUTS,
} outputsName_t;

typedef struct {
    unsigned int gpioOutput;
    unsigned int valueOutput;
} outputs_t;
/* ============================================================
 *  Extern Variables
 * ============================================================*/


/* ============================================================
 *  Function Prototypes
 * ============================================================*/
void output_Init(gpiod_chip *chip);
void output_RequestRelease();
#endif /* OUTPUT_H */
