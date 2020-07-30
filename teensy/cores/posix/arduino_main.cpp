/*
 *  Created on: 01.01.2019
 *      Author: Georgi Angelov
 */

#include <interface.h>

extern void setup();
extern void loop();

int main()
{
    printf("\nTeensy Linux Simulator 2020 WizIO\n");
    printDateTime();
    printf("\n");
    setup();
    while (true)
    {
        loop();
        delay(1); // can be REM
    }
}

