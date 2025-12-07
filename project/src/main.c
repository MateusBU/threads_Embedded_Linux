#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "bsp.h"
#include "input.h"
#include "output.h"

/* ============================================================
 *  Defines / Macros
 * ============================================================*/

/* ============================================================
 *  Static (private) variables
 * ============================================================*/

/* ============================================================
*  Static (private) functions
* ============================================================*/
void* blink_led(void *arg);
void* read_sensor(void *arg);

/* ============================================================
 *  Public functions
 * ============================================================*/

int main(void) {
    pthread_t th1, th2;

    pthread_create(&th1, NULL, blink_led, NULL);

    pthread_create(&th2, NULL, read_sensor, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    return 0;
}

void* blink_led(void *arg) {
    printf("Config LED\n");

    for(;;) {
        printf("LED Blink \n");
        usleep(1000000);
    }
}

void* read_sensor(void *arg) {
    printf("Config SENSOR\n");
    
    for(;;) {
        printf("Sensor read \n");
        usleep(700000);
    }
}