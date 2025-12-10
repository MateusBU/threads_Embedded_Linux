#include "bsp.h"
#include "input.h"
#include "output.h"

#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

/* ============================================================
 *  Static (private) variables
 * ============================================================*/

typedef enum {
    eCONFIG_GPIO_OK,
    eCONFIG_GPIOS_CHIP_ERROR,
    eCONFIG_GPIOS_LINE_ERROR,  
} configGpios_t;

const char *chip_path = "/dev/gpiochip0";
struct gpiod_chip *chip;

/* ============================================================
 *  Static (private) functions
 * ============================================================*/

/* ============================================================
 *  Public functions
 * ============================================================*/
void bsp_Init() {

    chip = gpiod_chip_open(chip_path);
    if (!chip) {
        perror("Failed to open gpiochip");
        return;
    }

    input_Init(chip);
    output_Init(chip);
    printf("output_Init: %d", 1);
}

void bsp_closeGPIOs() {
    output_RequestRelease();
    input_RequestRelease();
    gpiod_chip_close(chip);
}
/* ============================================================
 *  Private functions (static)
 * ============================================================*/
