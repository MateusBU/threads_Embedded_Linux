#include "output.h"

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

/* ============================================================
 *  Defines / Macros
 * ============================================================*/
#define GPIO_YELLOW_LED (18)

/* ============================================================
 *  Static (private) variables
 * ============================================================*/

typedef struct {
    unsigned int gpioOutput;
    unsigned int valueOutput;
} outputs_t;
struct gpiod_line_request *reqInput;

outputs_t outputs[eNUMBER_OF_OUTPUTS];
/* ============================================================
 *  Static (private) functions
 * ============================================================*/

/* ============================================================
 *  Public functions
 * ============================================================*/
void output_Init(struct gpiod_chip *chip) {

    /* Assign GPIO number for the output */
    outputs[eLED_YELLOW].gpioOutput = GPIO_YELLOW_LED;

    /* Configure the line as output */
    struct gpiod_line_settings *settings = gpiod_line_settings_new();
    gpiod_line_settings_set_direction(settings, GPIOD_LINE_DIRECTION_OUTPUT);

    struct gpiod_line_config *line_cfg = gpiod_line_config_new();
    gpiod_line_config_add_line_settings(
        line_cfg,
        &outputs[eLED_YELLOW].gpioOutput,
        1,
        settings
    );

    reqInput = gpiod_chip_request_lines(chip, NULL, line_cfg);
    if (!reqInput) {
        perror("Failed to request line");
        return;
    }

    return;    
}

void output_RequestRelease() {
    gpiod_line_request_release(reqInput);
}

/* ============================================================
 *  Private functions (static)
 * ============================================================*/
