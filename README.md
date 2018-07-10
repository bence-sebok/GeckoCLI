# GeckoCLI
An embedded CLI application for a Giant Gecko microcontroller based development board. The main feature is a command line interpreter in C and Qt C++ which controls the hardware components with serial commands from a PC.

There are two main parts of the application:
1. Embedded application
2. Graphical PC application

The embedded application is written in C and runs in a FreeRTOS operating system on a EFM32GG microcontroller.
The graphical PC application is written in C and C++ and runs in a Linux operating system on a simple PC.

## Embedded application
### Application logic
1. Waiting for a new command
2. Receives command from a PC (using serial communication: UART)
   * For example: `SETLED1` command sets LED 1
3. Processing the received command
4. Hardware management
   * Setting, getting values of LEDs
   * Writing to LCD display
5. Sending status message or response to the received command
6. Go to step 1

## Graphical PC application
