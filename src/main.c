
//#define BUTTON_BLINK
// #define LIGHT_SCHEDULER
// #define TIME_RAND
// #define KEYPAD
// #define KEYPAD_CONTROL
// #define SEVEN_SEGMENT
// #define KEYPAD_SEVEN_SEGMENT
// #define COLOR_LED
// #define ROTARY_ENCODER
// #define ANALOG
// #define PWM

#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions
#include <time.h>
#include "ece198.h"

int main(void) {
    HAL_Init(); // initialize the Hardware Abstraction Layer

    // Peripherals (including GPIOs) are disabled by default to save power, so we
    // use the Reset and Clock Control registers to enable the GPIO peripherals that we're using.

    __HAL_RCC_GPIOA_CLK_ENABLE(); // enable port A (for the on-board LED, for example)
    __HAL_RCC_GPIOB_CLK_ENABLE(); // enable port B (for the rotary encoder inputs, for example)
    __HAL_RCC_GPIOC_CLK_ENABLE(); // enable port C (for the on-board blue pushbutton, for example)

    // initialize the pins to be input, output, alternate function, etc...

      // on-board LED
    InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);

    //left side direction pins
    InitializePin(GPIOA, GPIO_PIN_10, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOB, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);

    //right side direction pins
    InitializePin(GPIOA, GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOA, GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);

    // note: the on-board pushbutton is fine with the default values (no internal pull-up resistor
    // is required, since there's one on the board)

    // set up for serial communication to the host computer
    // (anything we write to the serial port will appear in the terminal (i.e. serial monitor) in VSCode)
    HAL_Delay(100);
    SerialSetup(9600);
    // as mentioned above, only one of the following code sections will be used
    // (depending on which of the #define statements at the top of this file has been uncommented)
    uint32_t signal_timer = 0;
    uint32_t last_time = 0;
    // int allowance_short = 0;
    // int allowance_long = 0;
    bool pressed = false;
    // last 5 is an array that stores the last 5 dashes/dots, -1 meaning no value
    int last_5[5] = {-1,-1,-1,-1,-1};
    // last 2 is an array that stores the last 2 characters(for ex: f,b,2,6), -1 means no value
    int last_2_characters[2] = {-1,-1};
    //for these arrays they are reset by setting all values to -1
    // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
    // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);

    while (true) {
                    uint32_t now = HAL_GetTick();
        if (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)) {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
            signal_timer++;
            pressed = true;
        } else {
            HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5, 0);
            last_time = signal_timer;
            signal_timer = 0;
            pressed = false;
        }
        if (last_time != 0 && last_time < 100000) {
            SerialPuts(".");
            last_time = 0;
            last_5[0] = last_5[1];
            last_5[1] = last_5[2];
            last_5[2] = last_5[3];
            last_5[3] = last_5[4];
            last_5[4] = 0;
        }
        if (last_time > 1000) {
            SerialPuts("-");
            last_time = 0;
            last_5[0] = last_5[1];
            last_5[1] = last_5[2];
            last_5[2] = last_5[3];
            last_5[3] = last_5[4];
            last_5[4] = 1;
        }
        if (last_5[1] == 0 && last_5[2] == 0 && last_5[3] == 1 && last_5[4] == 0) {
            SerialPuts("F");
            last_5[0] = -1;
            last_5[1] = -1;
            last_5[2] = -1;
            last_5[3] = -1;
            last_5[4] = -1;
            last_2_characters[0] =  last_2_characters[1];
            last_2_characters[1] = 11;
        }
        if (last_5[1] == 1 && last_5[2] == 0 && last_5[3] == 0 && last_5[4] == 0) {
            SerialPuts("B");
            last_5[0] = -1;
            last_5[1] = -1;
            last_5[2] = -1;
            last_5[3] = -1;
            last_5[4] = -1;
            last_2_characters[0] =  last_2_characters[1];
            last_2_characters[1] = 0;
        }
        if (last_5[0] == 0 && last_5[1] == 1 && last_5[2] == 1 && last_5[3] == 1 && last_5[4] == 1) {
            SerialPuts("1");
            last_5[0] = -1;
            last_5[1] = -1;
            last_5[2] = -1;
            last_5[3] = -1;
            last_5[4] = -1;
            last_2_characters[0] =  last_2_characters[1];
            last_2_characters[1] = 1;
        }
            if (last_5[0] == 0 && last_5[1] == 0 && last_5[2] == 1 && last_5[3] == 1 && last_5[4] == 1) {
            SerialPuts("2");
            last_5[0] = -1;
            last_5[1] = -1;
            last_5[2] = -1;
            last_5[3] = -1;
            last_5[4] = -1;
            last_2_characters[0] =  last_2_characters[1];
            last_2_characters[1] = 2;
        }
    
            if (last_5[0] == 0 && last_5[1] == 0 && last_5[2] == 0 && last_5[3] == 1 && last_5[4] == 1) {
            SerialPuts("3");
            last_5[0] = -1;
            last_5[1] = -1;
            last_5[2] = -1;
            last_5[3] = -1;
            last_5[4] = -1;
            last_2_characters[0] =  last_2_characters[1];
            last_2_characters[1] = 3;
        }
                    if (last_5[0] == 0 && last_5[1] == 0 && last_5[2] == 0 && last_5[3] == 0 && last_5[4] == 1) {
            SerialPuts("4");
            last_5[0] = -1;
            last_5[1] = -1;
            last_5[2] = -1;
            last_5[3] = -1;
            last_5[4] = -1;
            last_2_characters[0] =  last_2_characters[1];
            last_2_characters[1] = 4;
        }
                    if (last_5[0] == 0 && last_5[1] == 0 && last_5[2] == 0 && last_5[3] == 0 && last_5[4] == 0) {
            SerialPuts("5");
            last_5[0] = -1;
            last_5[1] = -1;
            last_5[2] = -1;
            last_5[3] = -1;
            last_5[4] = -1;
            last_2_characters[0] =  last_2_characters[1];
            last_2_characters[1] = 5;
        }
                    if (last_5[0] == 1 && last_5[1] == 0 && last_5[2] == 0 && last_5[3] == 0 && last_5[4] == 0) {
            SerialPuts("6");
            last_5[0] = -1;
            last_5[1] = -1;
            last_5[2] = -1;
            last_5[3] = -1;
            last_5[4] = -1;
            last_2_characters[0] =  last_2_characters[1];
            last_2_characters[1] = 6;
        }
                    if (last_5[0] == 1 && last_5[1] == 1 && last_5[2] == 0 && last_5[3] == 0 && last_5[4] == 0) {
            SerialPuts("7");
            last_5[0] = -1;
            last_5[1] = -1;
            last_5[2] = -1;
            last_5[3] = -1;
            last_5[4] = -1;
            last_2_characters[0] =  last_2_characters[1];
            last_2_characters[1] = 7;
        }
                    if (last_5[0] == 1 && last_5[1] == 1 && last_5[2] == 1 && last_5[3] == 0 && last_5[4] == 0) {
            SerialPuts("8");
            last_5[0] = -1;
            last_5[1] = -1;
            last_5[2] = -1;
            last_5[3] = -1;
            last_5[4] = -1;
            last_2_characters[0] =  last_2_characters[1];
            last_2_characters[1] = 8;
        }
                    if (last_5[0] == 1 && last_5[1] == 1 && last_5[2] == 1 && last_5[3] == 1 && last_5[4] == 0) {
            SerialPuts("9");
            last_5[0] = -1;
            last_5[1] = -1;
            last_5[2] = -1;
            last_5[3] = -1;
            last_5[4] = -1;
            last_2_characters[0] =  last_2_characters[1];
            last_2_characters[1] = 9;
        }
        // rememeber 11 represents forwards and 0 represents backwards
        //  setting GPIOA_10 and GPIOB_5 to high will make motors go forwards
        //  setting GPIOA_8 and GPIOB_9 to high will make motors go backwards
        if (last_2_characters[0] == 11 && last_2_characters[1] > 0 && last_2_characters[1] < 10) {
            if (last_2_characters[1] == 1) {
                uint32_t start = HAL_GetTick();
                uint32_t end = start + 1000;
                while (start < end) {
                    start = HAL_GetTick();
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
                    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
                }
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);
                last_2_characters[0] = -1;
                last_2_characters[1] = -1;
            }
            if (last_2_characters[1] == 2) {
                uint32_t start = HAL_GetTick();
                uint32_t end = start + 2000;
                while (start < end) {
                    start = HAL_GetTick();
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
                    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
                }
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);
                last_2_characters[0] = -1;
                last_2_characters[1] = -1;
            }
            if (last_2_characters[1] == 3) {
                uint32_t start = HAL_GetTick();
                uint32_t end = start + 3000;
                while (start < end) {
                    start = HAL_GetTick();
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
                    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
                }
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);
                last_2_characters[0] = -1;
                last_2_characters[1] = -1;
            }
            if (last_2_characters[1] == 4) {
                uint32_t start = HAL_GetTick();
                uint32_t end = start + 4000;
                while (start < end) {
                    start = HAL_GetTick();
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
                    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
                }
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);
                last_2_characters[0] = -1;
                last_2_characters[1] = -1;
            }
            if (last_2_characters[1] == 5) {
                uint32_t start = HAL_GetTick();
                uint32_t end = start + 5000;
                while (start < end) {
                    start = HAL_GetTick();
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
                    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
                }
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);
                last_2_characters[0] = -1;
                last_2_characters[1] = -1;
            }
            if (last_2_characters[1] == 6) {
                uint32_t start = HAL_GetTick();
                uint32_t end = start + 6000;
                while (start < end) {
                    start = HAL_GetTick();
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
                    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
                }
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);
                last_2_characters[0] = -1;
                last_2_characters[1] = -1;
            }
            if (last_2_characters[1] == 7) {
                uint32_t start = HAL_GetTick();
                uint32_t end = start + 7000;
                while (start < end) {
                    start = HAL_GetTick();
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
                    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
                }
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);
                last_2_characters[0] = -1;
                last_2_characters[1] = -1;
            }
            if (last_2_characters[1] == 8) {
                uint32_t start = HAL_GetTick();
                uint32_t end = start + 8000;
                while (start < end) {
                    start = HAL_GetTick();
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
                    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
                }
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);
                last_2_characters[0] = -1;
                last_2_characters[1] = -1;
            }
            if (last_2_characters[1] == 9) {
                uint32_t start = HAL_GetTick();
                uint32_t end = start + 9000;
                while (start < end) {
                    start = HAL_GetTick();
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
                    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
                }
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);
                last_2_characters[0] = -1;
                last_2_characters[1] = -1;
            }
        } else {
             HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
        }
        if (last_2_characters[0] == 0 && last_2_characters[1] > 0 && last_2_characters[1] < 10) {
            if (last_2_characters[1] == 1) {
                uint32_t start = HAL_GetTick();
                uint32_t end = start + 1000;
                while (start < end) {
                    start = HAL_GetTick();
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 1);
                }
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 0);
                last_2_characters[0] = -1;
                last_2_characters[1] = -1;
            }
            if (last_2_characters[1] == 2) {
                uint32_t start = HAL_GetTick();
                uint32_t end = start + 2000;
                while (start < end) {
                    start = HAL_GetTick();
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 1);
                }
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 0);
                last_2_characters[0] = -1;
                last_2_characters[1] = -1;
            }
            if (last_2_characters[1] == 3) {
                uint32_t start = HAL_GetTick();
                uint32_t end = start + 3000;
                while (start < end) {
                    start = HAL_GetTick();
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 1);
                }
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 0);
                last_2_characters[0] = -1;
                last_2_characters[1] = -1;
            }
            if (last_2_characters[1] == 4) {
                uint32_t start = HAL_GetTick();
                uint32_t end = start + 4000;
                while (start < end) {
                    start = HAL_GetTick();
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 1);
                }
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 0);
                last_2_characters[0] = -1;
                last_2_characters[1] = -1;
            }
            if (last_2_characters[1] == 5) {
                uint32_t start = HAL_GetTick();
                uint32_t end = start + 5000;
                while (start < end) {
                    start = HAL_GetTick();
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 1);
                }
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 0);
                last_2_characters[0] = -1;
                last_2_characters[1] = -1;
            }
            if (last_2_characters[1] == 6) {
                uint32_t start = HAL_GetTick();
                uint32_t end = start + 6000;
                while (start < end) {
                    start = HAL_GetTick();
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 1);
                }
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 0);
                last_2_characters[0] = -1;
                last_2_characters[1] = -1;
            }
            if (last_2_characters[1] == 7) {
                uint32_t start = HAL_GetTick();
                uint32_t end = start + 7000;
                while (start < end) {
                    start = HAL_GetTick();
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 1);
                }
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 0);
                last_2_characters[0] = -1;
                last_2_characters[1] = -1;
            }
            if (last_2_characters[1] == 8) {
                uint32_t start = HAL_GetTick();
                uint32_t end = start + 8000;
                while (start < end) {
                    start = HAL_GetTick();
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 1);
                }
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 0);
                last_2_characters[0] = -1;
                last_2_characters[1] = -1;
            }
            if (last_2_characters[1] == 9) {
                uint32_t start = HAL_GetTick();
                uint32_t end = start + 9000;
                while (start < end) {
                    start = HAL_GetTick();
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 1);
                }
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 0);
                last_2_characters[0] = -1;
                last_2_characters[1] = -1;
            }
        } else {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);
        }
    }
#ifdef BUTTON_BLINK
    // Wait for the user to push the blue button, then blink the LED.

    // wait for button press (active low)
    while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13))
    {
    }

    while (1) // loop forever, blinking the LED
    {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        HAL_Delay(1000);  // 250 milliseconds == 1/4 second
    }
#endif

#ifdef LIGHT_SCHEDULER
    // Turn on the LED five seconds after reset, and turn it off again five seconds later.

    // while (true) {
        /*uint32_t now = HAL_GetTick();
        if (now < 50)
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, true);   // turn on LED
        else
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, false);  // turn off LED\
        */
    //    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)) {
    //        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, false);
    //    } else {
    //        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, true);
    //    }
    // }
 #endif

#ifdef TIME_RAND
    // This illustrates the use of HAL_GetTick() to get the current time,
    // plus the use of random() for random number generation.
    
    // Note that you must have "#include <stdlib.h>"" at the top of your main.c
    // in order to use the srand() and random() functions.

    // while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));  // wait for button press
    // srand(HAL_GetTick());  // set the random seed to be the time in ms that it took to press the button
    // if the line above is commented out, your program will get the same sequence of random numbers
    // every time you run it (which may be useful in some cases)

    while (true) // loop forever
    {
        while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));  // wait for button press

        // Display the time in milliseconds along with a random number.
        // We use the sprintf() function to put the formatted output into a buffer;
        // see https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm for more
        // information about this function
        char buff[100];
        sprintf(buff, "Time: %lu ms   Random = %ld\r\n", HAL_GetTick(), random());
        // lu == "long unsigned", ld = "long decimal", where "long" is 32 bit and "decimal" implies signed
        SerialPuts(buff); // transmit the buffer to the host computer's serial monitor in VSCode/PlatformIO

        while (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));  // wait for button to be released
    }
#endif

#ifdef KEYPAD
    // Read buttons on the keypad and display them on the console.

    // this string contains the symbols on the external keypad
    // (they may be different for different keypads)
    char *keypad_symbols = "123A456B789C*0#D";
    // note that they're numbered from left to right and top to bottom, like reading words on a page

    InitializeKeypad();
    while (true)
    {
        while (ReadKeypad() < 0);   // wait for a valid key
        SerialPutc(keypad_symbols[ReadKeypad()]);  // look up its ASCII symbol and send it to the hsot
        while (ReadKeypad() >= 0);  // wait until key is released
    }
#endif

#ifdef KEYPAD_CONTROL
    // Use top-right button on 4x4 keypad (typically 'A') to toggle LED.

    InitializeKeypad();
    while (true)
    {
        while (ReadKeypad() < 0);   // wait for a valid key
        int key = ReadKeypad();
        if (key == 3)  // top-right key in a 4x4 keypad, usually 'A'
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);   // toggle LED on or off
         while (ReadKeypad() >= 0);  // wait until key is released
    }
#endif

#ifdef SEVEN_SEGMENT
    // Display the numbers 0 to 9 inclusive on the 7-segment display, pausing for a second between each one.
    // (remember that the GND connection on the display must go through a 220 ohm current-limiting resistor!)
    
    Initialize7Segment();
    while (true)
        for (int i = 0; i < 10; ++i)
        {
            Display7Segment(i);
            HAL_Delay(1000);  // 1000 milliseconds == 1 second
        }
#endif

#ifdef KEYPAD_SEVEN_SEGMENT
    // Combines the previous two examples, displaying numbers from the keypad on the 7-segment display.

    // this string contains the symbols on the external keypad
    // (they may be different for different keypads)
    char *keypad_symbols = "123A456B789C*0#D";
    // note that they're numbered from left to right and top to bottom, like reading words on a page

    InitializeKeypad();
    Initialize7Segment();
    while (true)
    {
        int key = ReadKeypad();
        if (key >= 0)
            Display7Segment(keypad_symbols[key]-'0');  // tricky code to convert ASCII digit to a number
    }
#endif

#ifdef COLOR_LED
    // Cycle through all 8 possible colors (including off and white) as the on-board button is pressed.
    // This example assumes that the color LED is connected to pins D11, D12 and D13.

    // Remember that each of those three pins must go through a 220 ohm current-limiting resistor!
    // Also remember that the longest pin on the LED should be hooked up to GND.

    InitializePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // initialize color LED output pins
    while (true) {
        for (int color = 0; color < 8; ++color) {
            // bottom three bits indicate which of the three LEDs should be on (eight possible combinations)
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, color & 0x01);  // blue  (hex 1 == 0001 binary)
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, color & 0x02);  // green (hex 2 == 0010 binary)
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, color & 0x04);  // red   (hex 4 == 0100 binary)

            while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));   // wait for button press 
            while (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));  // wait for button release
        }
    }
#endif

#ifdef ROTARY_ENCODER
    // Read values from the rotary encoder and update a count, which is displayed in the console.

    InitializePin(GPIOB, GPIO_PIN_5, GPIO_MODE_INPUT, GPIO_PULLUP, 0);   // initialize CLK pin
    InitializePin(GPIOB, GPIO_PIN_4, GPIO_MODE_INPUT, GPIO_PULLUP, 0);   // initialize DT pin
    InitializePin(GPIOB, GPIO_PIN_10, GPIO_MODE_INPUT, GPIO_PULLUP, 0);  // initialize SW pin
    
    bool previousClk = false;  // needed by ReadEncoder() to store the previous state of the CLK pin
    int count = 0;             // this gets incremented or decremented as we rotate the encoder

    while (true)
    {
        int delta = ReadEncoder(GPIOB, GPIO_PIN_5, GPIOB, GPIO_PIN_4, &previousClk);  // update the count by -1, 0 or +1
        if (delta != 0) {
            count += delta;
            char buff[100];
            sprintf(buff, "%d  \r", count);
            SerialPuts(buff);
        }
        bool sw = !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10);  // read the push-switch on the encoder (active low, so we invert it using !)
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, sw);  // turn on LED when encoder switch is pushed in
    }
#endif

#ifdef ANALOG
    // Use the ADC (Analog to Digital Converter) to read voltage values from two pins.

    __HAL_RCC_ADC1_CLK_ENABLE();        // enable ADC 1
    ADC_HandleTypeDef adcInstance;      // this variable stores an instance of the ADC
    InitializeADC(&adcInstance, ADC1);  // initialize the ADC instance
    // Enables the input pins
    // (on this board, pin A0 is connected to channel 0 of ADC1, and A1 is connected to channel 1 of ADC1)
    InitializePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1, GPIO_MODE_ANALOG, GPIO_NOPULL, 0);   
    while (true)
    {
        // read the ADC values (0 -> 0V, 2^12 -> 3.3V)
        uint16_t raw0 = ReadADC(&adcInstance, ADC_CHANNEL_0);
        uint16_t raw1 = ReadADC(&adcInstance, ADC_CHANNEL_1);

        // print the ADC values
        char buff[100];
        sprintf(buff, "Channel0: %hu, Channel1: %hu\r\n", raw0, raw1);  // hu == "unsigned short" (16 bit)
        SerialPuts(buff);
    }
#endif

#ifdef PWM
    // Use Pulse Width Modulation to fade the LED in and out.
    uint16_t period = 100, prescale = 16;

    __TIM2_CLK_ENABLE();  // enable timer 2
    TIM_HandleTypeDef pwmTimerInstance;  // this variable stores an instance of the timer
    InitializePWMTimer(&pwmTimerInstance, TIM2, period, prescale);   // initialize the timer instance
    InitializePWMChannel(&pwmTimerInstance, TIM_CHANNEL_1);          // initialize one channel (can use others for motors, etc)

    InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_AF1_TIM2); // connect the LED to the timer output

    while (true)
    {
        // fade the LED in by slowly increasing the duty cycle
        for (uint32_t i = 0; i < period; ++i)
        {
            SetPWMDutyCycle(&pwmTimerInstance, TIM_CHANNEL_1, i);
            HAL_Delay(5);
        }
        // fade the LED out by slowly decreasing the duty cycle
        for (uint32_t i = period; i > 0; --i)
        {
            SetPWMDutyCycle(&pwmTimerInstance, TIM_CHANNEL_1, i);
            HAL_Delay(5);
        }
    }
#endif
    return 0;
}

// This function is called by the HAL once every millisecond
void SysTick_Handler(void)
{

    HAL_IncTick();
    //HAL_IncTick();  tell HAL that a new tick has happened
    // we can do other things in here too if we need to, but be careful
}
