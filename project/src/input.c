#include "input.h"

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

/* ============================================================
 *  Defines / Macros
 * ============================================================*/
#define GPIO_BUTTON_1 (22)

/* ============================================================
 *  Static (private) variables
 * ============================================================*/

typedef struct {
    unsigned int gpioInput;
    int valueInput;
} inputs_t;

struct gpiod_line_request *req;
inputs_t inputs[eNUMBER_OF_INPUTS];

/* ============================================================
 *  Static (private) functions
 * ============================================================*/

/* ============================================================
 *  Public functions
 * ============================================================*/

void input_Init(gpiod_chip *chip) {

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

    req = gpiod_chip_request_lines(chip, NULL, line_cfg);
    if (!req) {
        perror("Failed to request input line");
    }
}

void input_RequestRelease() {
    gpiod_line_request_release(req);
}

int input_GetValue(inputsName_t input) {
    if(input >= eNUMBER_OF_INPUTS) {
        return 0;
    }
    return inputs[input].valueInput;
}
/* ============================================================
 *  Private functions (static)
 * ============================================================*/
