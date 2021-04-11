#include <stdio.h>
#include <math.h>
#include "contiki.h"
#include "ECG.h"

/**
 * @ THIS PROGRAM HAS ONLY BEEN TESTED IN A SIMULATED ENVIROMENT (COOJA)
 * 
 * @ Author: Peter Marcus Hoveling
 * @ Date: 31/03/2021
*/

/* PROTOTYPING */
void dctTransform(u_int8_t chosen_n, u_int8_t chosen_m);

/* GLOBAL */
static double dctTransformedSignal[512];
static u_int8_t chosen_n = 100;
static u_int8_t chosen_m = 70;


/*-----------------------------------------------------------*/
PROCESS(signalDataCompression, "data compression using discrete cosine transform (DCT)");
PROCESS(arrayCounter, "Checking array is as long as aspected");
AUTOSTART_PROCESSES(&signalDataCompression);
/*-----------------------------------------------------------*/

/**
 * Initial process
 * ---
 * Arguments: 
 * Retruns: 
*/
PROCESS_THREAD(signalDataCompression, ev, data)
{
    PROCESS_BEGIN();
    process_start(&arrayCounter, NULL);
    PROCESS_END();
}

PROCESS_THREAD(arrayCounter, ev, data)
{
    PROCESS_BEGIN();
    dctTransform(chosen_n, chosen_m);
    // int arraySize = sizeof(dctTransformedSignal) / sizeof(dctTransformedSignal[0]);
    printf("Array size: %d \n", chosen_n);
    int i;
    for(i = 0; i < chosen_n; i++){
        printf(" ");
        printFloat(dctTransformedSignal[i]);
    }

    printf("Number of items: %d \n", i);

    PROCESS_END();
}


void dctTransform(u_int8_t chosen_n, u_int8_t chosen_m){
    //int arraySize = sizeof(ECGSignal) / sizeof(ECGSignal[0]);
    double divisionConstant = M_PI/chosen_n;
    int k;
    int n;

    for(k = 0; k < chosen_n; k++){
        dctTransformedSignal[k] = 0;
        printf("LOOP 1 %d\n", k);
        for(n = 0; n < chosen_n; n++){
            dctTransformedSignal[k] = dctTransformedSignal[k] + ECGSignal[n]*cos(divisionConstant*((n+0.5)*k));
        }
    }
    printf("Done with DCT transformation! \n");
}
