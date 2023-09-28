#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"

//*****************************************************************************
// Setting up the system clock
//*****************************************************************************
void ConfigureSystemClock() {
    // Setup the system clock to run at 80 MHz from PLL with crystal reference
    MAP_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
}

//*****************************************************************************
// Send a string to the UART.
//*****************************************************************************
void UARTSend(const char *pui8Buffer, uint32_t ui32Count) {
    while (ui32Count--) {
        // Write the next character to the UART.
        MAP_UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);
    }
}

//*****************************************************************************
// The interrupt handler for PortE1
//*****************************************************************************
void PortEIntHandler(void) {
    // Clear Interrupt flag
    MAP_GPIOIntClear(GPIO_PORTE_BASE, GPIO_INT_PIN_1);

    // Every time PE1 change state from LOW to HIGH, an trigger is sent
    if (MAP_GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_1) == 0x2) {
        UARTSend("T", 1);
        MAP_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0xFF);
    } else {
        MAP_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0x00);
    }

}

//*****************************************************************************
// Setting up the IO pins
//*****************************************************************************
void ConfigureIOPorts() {
//////// Port E

    // Enable and wait for the port to be ready for access
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while (!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)) {}

    // Configure the pins E1 to be the input clocks
    MAP_GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_1);

    // When this PE1 changes its state, an interrupt will be issued
    MAP_GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_1);
    MAP_GPIOIntTypeSet(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_BOTH_EDGES);
    MAP_GPIOIntRegister(GPIO_PORTE_BASE, &PortEIntHandler);
    MAP_GPIOIntEnable(GPIO_PORTE_BASE, GPIO_INT_PIN_1);

//////// Port B

    // Enable and wait for the port to be ready for access
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while (!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)) {}

    // Configure the pins B[0-7] to be the output
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
}

//*****************************************************************************
// Configure UART Communication
//*****************************************************************************
void ConfigureUART() {
    // Enable the peripherals used by this example.
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Enable processor interrupts.
    MAP_IntMasterEnable();

    // Set GPIO A0 and A1 as UART pins.
    MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
    MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Configure the UART for 115,200, 8-N-1 operation.
    MAP_UARTConfigSetExpClk(UART0_BASE, MAP_SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    // Enable the UART interrupt.
    MAP_IntEnable(INT_UART0);
    MAP_UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
}

//*****************************************************************************
// Main 'C' Language entry point.
//*****************************************************************************
int main(void) {
    ConfigureSystemClock();
    ConfigureIOPorts();
    ConfigureUART();

    while (1) {}
}
