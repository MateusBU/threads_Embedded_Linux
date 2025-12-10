#include "input.h"

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

/* ============================================================
 *  Defines / Macros
 * ============================================================*/
#define GPIO_BUTTON_1 (22)
#define DEBOUNCE 10
/* ============================================================
 *  Static (private) variables
 * ============================================================*/

typedef struct {
    unsigned int gpioInput;
    int valueInput;
    int valueHigh;
    int valueLow;
    bool edgeRise;
    bool edgeFall;
    int oldValue;
} inputs_t;

struct gpiod_line_request *reqInput;
inputs_t inputs[eNUMBER_OF_INPUTS];

/* ============================================================
 *  Static (private) functions
 * ============================================================*/

/* ============================================================
 *  Public functions
 * ============================================================*/

void input_Init(struct gpiod_chip *chip) {

    /* Assign GPIO number for the input */
    inputs[eBUTTON_1].gpioInput = GPIO_BUTTON_1;

    struct gpiod_line_settings *settings = gpiod_line_settings_new();
    gpiod_line_settings_set_direction(settings, GPIOD_LINE_DIRECTION_INPUT);

    // Enable pull-up (important for buttons!)
    gpiod_line_settings_set_bias(settings, GPIOD_LINE_BIAS_PULL_UP);

    struct gpiod_line_config *line_cfg = gpiod_line_config_new();
    gpiod_line_config_add_line_settings(
        line_cfg,
        &inputs[eBUTTON_1].gpioInput,
        1,
        settings
    );

    reqInput = gpiod_chip_request_lines(chip, NULL, line_cfg);
    if (!reqInput) {
        perror("Failed to request input line");
    }
}

void input_RequestRelease() {
    gpiod_line_request_release(reqInput);
}

int input_GetValue(inputsName_t input) {
    if(input >= eNUMBER_OF_INPUTS) {
        return 0;
    }
    return inputs[input].valueInput;
}

bool input_GetRise(inputsName_t input) {
    bool aux = inputs[input].edgeRise;
    inputs[input].edgeRise = 0;
    return aux;
}

bool input_GetFall(inputsName_t input) {
    bool aux = inputs[input].edgeFall;
    inputs[input].edgeFall = 0;
    return aux;
}

void input_Periodic() {

    for(int i = 0; i < eNUMBER_OF_INPUTS; i++) {
        int value = gpiod_line_request_get_value(reqInput, inputs[i].gpioInput);

        if(value == 1) {
            inputs[i].valueLow = 0;
            if(++inputs[i].valueHigh >= DEBOUNCE)
            {
                inputs[i].valueHigh = 0;
                inputs[i].valueInput = 1;
            }
        }
        else {
            inputs[i].valueHigh = 0;
            if(++inputs[i].valueLow >= DEBOUNCE)
            {
                inputs[i].valueLow = 0;
                inputs[i].valueInput = 0;
            }
        }
        if((inputs[i].oldValue == 0) && (inputs[i].valueInput == 1)) {
            inputs[i].edgeRise = 1;
            inputs[i].edgeFall = 0;
        }
        else if((inputs[i].oldValue == 1) && (inputs[i].valueInput == 0)) {
            inputs[i].edgeRise = 0;
            inputs[i].edgeFall = 1;
        }
        inputs[i].oldValue = inputs[i].valueInput;
    }

}
/* ============================================================
 *  Private functions (static)
 * ============================================================*/
