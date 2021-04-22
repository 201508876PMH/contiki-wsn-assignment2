#include <stdio.h>
#include <math.h>
#include "contiki.h"
#include "ECG.h"

/**
 * @ THIS PROGRAM HAS ONLY BEEN TESTED IN A SIMULATED ENVIRONMENT (COOJA)
 * 
 * @ Author: Peter Marcus Hoveling
 * @ Date: 15/04/2021
*/

/* PROTOTYPING */
void dctTransformChoice(int number);
void dctTransform256();
void dctTransform512();

/* GLOBAL */
static double dctTransformedSignal[512];

/*-----------------------------------------------------------*/
PROCESS(signalDataCompression, "data compression using discrete cosine transform (DCT)");
PROCESS(arrayPrinter, "Print output");
AUTOSTART_PROCESSES(&signalDataCompression);
/*-----------------------------------------------------------*/

PROCESS_THREAD(signalDataCompression, ev, data)
{
    PROCESS_BEGIN();
    process_start(&arrayPrinter, (int *)512); //<--- Change value here (256/512)
    PROCESS_END();
}

/**
 * Process for printing output, whilst also calling the chosen dct
 * ---
 * Arguments: arrayPrinter, ev, data (either 256 or 512)
 * Retruns: none 
*/
PROCESS_THREAD(arrayPrinter, ev, data)
{
    PROCESS_BEGIN();
    clock_init();

    unsigned long timer_start = clock_seconds();
    printf("Timer has started! %lu \n", timer_start);
    dctTransformChoice((int)data);
    unsigned long timer_end = clock_seconds();
    printf("Total time for N = %d, %lu seconds\n", (int)data, timer_end);

    printf("Array size: %d \n", (int)data);
    int i;
    for (i = 0; i < (int)data; i++)
    {
        printf(" ");
        printFloat(dctTransformedSignal[i]);
    }

    printf("Number of items: %d \n", i);

    PROCESS_END();
}

/**
 * Function for choosing which dct to choose
 * ---
 * Arguments: Either 256 or 512
 * Retruns: The chosen function
*/
void dctTransformChoice(int number)
{
    if (number == 256)
    {
        dctTransform256();
    }
    else if (number == 512)
    {
        dctTransform512();
    }
    else
    {
        printf("Invalid number!");
    }
}

/**
 * dct transformation function for N = 256
 * ---
 * Arguments: None
 * Retruns: None (void)
 * 
 * Time for N = 256:
 * 2659 seconds ~ 44.31 minutes 
 * Transformed output:
 * [-57.0  30.0  -22.0  9.0  -2.0  10.0  11.0  -6.0  16.0  -10.0  19.0  -7.0  14.0  -2.0  4.0  6.0  -3.0  10.0  -5.0  7.0  0.0  0.0  6.0  -6.0  8.0  -6.0  4.0  0.0  0.0  3.0  -3.0  3.0  -3.0  0.0  -1.0  -2.0  0.0  -3.0  0.0  -2.0  0.0  -1.0  -1.0  -1.0  -1.0  -1.0  0.0  -1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  1.0  0.0  1.0  0.0  1.0  0.0  0.0  1.0  0.0  1.0  0.0  1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  -1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0] 
*/

void dctTransform256()
{
    double divisionConstant = M_PI / 256;
    int k;
    int n;

    for (k = 0; k < 256; k++)
    {
        dctTransformedSignal[k] = 0;
        printf("LOOP 1 : %d\n", k);
        for (n = 0; n < 256; n++)
        {
            dctTransformedSignal[k] = dctTransformedSignal[k] + ECGSignal256[n] * cos(divisionConstant * ((n + 0.5) * k));
        }
    }
    printf("Done with DCT transformation! \n");
}


/**
 * dct transformation function for N = 512
 * ---
 * Arguments: None
 * Retruns: None (void)
 * 
 * Time for N = 512:
 * 14950 seconds ~ 249.167 minutes ~ 4.152 hours
 * Transformed output:
 * [-55.0  -14.0  11.0  27.0  1.0  -54.0  15.0  38.0  -10.0  -24.0  18.0  34.0  -1.0  -4.0  -12.0  27.0  4.0  7.0  -25.0  23.0  4.0  16.0  -19.0  12.0  4.0  20.0  -10.0  0.0  0.0  14.0  5.0  -4.0  0.0  1.0  17.0  -2.0  2.0  -11.0  15.0  0.0  9.0  -15.0  10.0  0.0  16.0  -13.0  0.0  -2.0  13.0  -2.0  -3.0  -4.0  6.0  5.0  -1.0  -3.0  -2.0  5.0  0.0  1.0  -7.0  3.0  0.0  5.0  -8.0  0.0  -3.0  5.0  -5.0  -1.0  -5.0  5.0  -2.0  0.0  -6.0  1.0  -2.0  0.0  -4.0  0.0  -1.0  0.0  -1.0  -1.0  -1.0  -3.0  0.0  -2.0  0.0  -3.0  1.0  -2.0  2.0  -4.0  1.0  -2.0  1.0  -3.0  1.0  -1.0  2.0  -1.0  1.0  -1.0  0.0  0.0  0.0  0.0  0.0  1.0  0.0  1.0  0.0  0.0  0.0  1.0  -1.0  1.0  0.0  2.0  0.0  0.0  0.0  2.0  0.0  0.0  0.0  2.0  1.0  2.0  1.0  1.0  0.0  1.0  0.0  0.0  0.0  0.0  1.0  0.0  0.0  0.0  1.0  0.0  0.0  0.0  1.0  0.0  1.0  0.0  1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  1.0  0.0  -1.0  0.0  0.0  0.0  -1.0  0.0  0.0  0.0  -1.0  0.0  -1.0  -1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  -1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  -1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  -1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  -1.0  0.0  0.0  1.0  0.0  0.0  0.0  0.0  -1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  1.0  0.0  0.0  0.0  0.0  0.0  0.0  -1.0  0.0  0.0  0.0  0.0  1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  -1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  -1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  -1.0  0.0  0.0  1.0  0.0  0.0  0.0  0.0  -1.0  0.0  0.0  1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  1.0  0.0  0.0  0.0  1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  -1.0  0.0  0.0  0.0  0.0  1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  1.0  0.0  0.0  0.0  0.0  -1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  -1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  1.0  0.0  0.0  -1.0  0.0  0.0  0.0  0.0  1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  -1.0  0.0  0.0  0.0  0.0  1.0  0.0  0.0  -1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  -1.0  0.0  0.0  0.0  0.0  0.0  0.0  1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  -1.0  0.0  0.0  0.0  0.0  1.0  0.0  0.0  0.0  0.0  0.0  0.0  0.0  1.0  0.0  0.0]
*/
void dctTransform512()
{
    double divisionConstant = M_PI / 512;
    int k;
    int n;

    for (k = 0; k < 512; k++)
    {
        dctTransformedSignal[k] = 0;
        printf("LOOP 1 : %d\n", k);
        for (n = 0; n < 512; n++)
        {
            dctTransformedSignal[k] = dctTransformedSignal[k] + ECGSignal512[n] * cos(divisionConstant * ((n + 0.5) * k));
        }
    }
    printf("Done with DCT transformation! \n");
}
