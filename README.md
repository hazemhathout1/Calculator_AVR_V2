# Calculator Application using AVR Atmega32

This application is a simple calculator developed using embedded C for the AVR Atmega32 microcontroller.

## Overview

The `Application.c` file contains the main logic of the calculator application. It performs basic arithmetic operations such as addition, subtraction, multiplication, and division. The application interfaces with an LED display and push buttons for user input.

## Features

- Basic arithmetic operations
- Clear screen functionality
- Input validation
- LED display output

## Hardware Requirements

- AVR Atmega32 microcontroller
- LED display
- Push buttons for input

## Usage

1. Connect the AVR Atmega32 microcontroller to the LED display and push buttons as per the hardware setup.
2. Compile and upload the code onto the microcontroller using an AVR programmer.
3. Power on the microcontroller.
4. Use the push buttons to input numbers and operators.
5. Press "=" button to perform the calculation.
6. Results will be displayed on the LED display.

## Project Structure

- `Application.c`: Contains the main logic of the calculator application.
- `Application.h`: Header file for the application.
- `lcd.h` and `lcd.c`: Driver files for interfacing with the LED display.
- `keypad.h` and `keypad.c`: Driver files for reading input from push buttons.
- `Makefile`: Makefile for building the project.

## How to Build

1. Ensure AVR-GCC and AVRDUDE are installed on your system.
2. Compile the code using the provided Makefile.
3. Upload the compiled code onto the AVR Atmega32 microcontroller using an AVR programmer.

## Contributors

- Hazem Hathout

