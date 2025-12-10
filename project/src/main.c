#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "app.h"
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
void* app_task(void *arg);
void* gpio_task(void *arg);

/* ============================================================
 *  Public functions
 * ============================================================*/

int main(void) {
    pthread_t th1, th2;

    pthread_create(&th1, NULL, app_task, NULL);

    pthread_create(&th2, NULL, gpio_task, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    return 0;
}

void* app_task(void *arg) {
    printf("Config APP\n");

    for(;;) {
        app_Periodic();
        usleep(100000);
    }
}

void* gpio_task(void *arg) {
    printf("Config GPIO I/O\n");
    bsp_Init();
    
    for(;;) {
        input_Periodic();
        output_Periodic();
        usleep(1000);
    }
}