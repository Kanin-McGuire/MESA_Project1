/**----------------------------------------------------------------------------
 
   \file main.cpp
--                                                                           --
--              ECEN 5803 Mastering Embedded System Architecture             --
--                  Project 1 Module 4                                       --
--                Microcontroller Firmware                                   --
--                      main.cpp                                             --
--                                                                           --
-------------------------------------------------------------------------------
--
--  Designed for:  University of Colorado at Boulder
--               
--                
--  Designed by:  Tim Scherr
--  Revised by:  Student's name 
-- 
-- Version: 2.1
-- Date of current revision:  2017-09-25   
-- Target Microcontroller: Freescale MKL25ZVMT4 
-- Tools used:  ARM mbed compiler
--              ARM mbed SDK
--              Freescale FRDM-KL25Z Freedom Board
--               
-- 
-- Functional Description:  Main code file generated by mbed, and then
--                           modified to implement a super loop bare metal OS.
--
--      Copyright (c) 2015, 2016 Tim Scherr  All rights reserved.
--
*/

#define MAIN
#include "shared.h"
#undef MAIN

#define ADC_0                   (0U)
#define CHANNEL_0               (0U)
#define CHANNEL_1               (1U)
#define CHANNEL_2               (2U)
#define LED_ON                  (0U)
#define LED_OFF                 (1U)
#define ADCR_VDD                (65535U)    /*! Maximum value when use 16b resolution */
#define V_BG                    (1000U)     /*! BANDGAP voltage in mV (trim to 1.0V) */
#define V_TEMP25                (716U)      /*! Typical VTEMP25 in mV */
#define M                       (1620U)     /*! Typical slope: (mV x 1000)/oC */
#define STANDARD_TEMP           (25)


extern volatile uint16_t SwTimerIsrCounter; 


Ticker tick;             //  Creates a timer interrupt using mbed methods
 /****************      ECEN 5803 add code as indicated   ***************/
                // Add code to control red, green and blue LEDs here
                                                    


Serial pc(USBTX, USBRX);
 
void flip() 
{
    greenLED = !greenLED;
}
 
int main() 
{
/****************      ECEN 5803 add code as indicated   ***************/
                    //  Add code to call timer0 function every 100 uS

    pc.printf("Hello World!\n"); 
    uint32_t  count = 0;   
    
// initialize serial buffer pointers
   rx_in_ptr =  rx_buf; /* pointer to the receive in data */
   rx_out_ptr = rx_buf; /* pointer to the receive out data*/
   tx_in_ptr =  tx_buf; /* pointer to the transmit in data*/
   tx_out_ptr = tx_buf; /*pointer to the transmit out */
    
   
  // Print the initial banner
    pc.printf("\r\nHello World!\n\n\r");

    /****************      ECEN 5803 add code as indicated   ***************/
    // uncomment this section after adding monitor code.  
   /* send a message to the terminal  */                    
   /*
   UART_direct_msg_put("\r\nSystem Reset\r\nCode ver. ");
   UART_direct_msg_put( CODE_VERSION );
   UART_direct_msg_put("\r\n");
   UART_direct_msg_put( COPYRIGHT );
   UART_direct_msg_put("\r\n");

   set_display_mode();                                      
   */
   

    while(1)       // Cyclical Executive Loop
    {

        count++;                  // counts the number of times through the loop
//      __enable_interrupts();
//      __clear_watchdog_timer();
       
        serial();            // Polls the serial port
        chk_UART_msg();     // checks for a serial port message received
        monitor();           // Sends serial port output messages depending
                         //  on commands received and display mode
 
   /****************      ECEN 5803 add code as indicated   ***************/
   
//  readADC()

//  calculate flow()
void flow(){
    d = .5; //% inches
    PID =  2.9; //% inches

    rho = 1000*(1 - ((T+288.9414)/(508929.2*(T+68.12963)))*(T-3.9863)^2);
    //%in kg/m^3 with T In degrees C.

    viscosity = (2.4 * (10^(-5))) * 10^(247.8/((T+273.15)-140.0)); //% t from cel to kelvin 
    //%kg/(m*s) = V T is in Kelvin

    Re = (rho * v * (PID*.0254)) / viscosity;

    St = .02684 - (1.0356/sqrt(Re));

    //%A = pi * (d * 0.0254)^2; % in meters maybe use PID not d??

    //%Q = Av;

    v = ((f*(d))/St) * 0.0254; //%m/s

}

//  4-20 output ()    // use TMP0 channel 3  proporional rate to flow

//  Pulse output()   // use TMP0 channel 4  propotional rate to frequency

//  LCD_Display()   // use the SPI port to send flow number

//  End ECEN 5803 code addition


        if ((SwTimerIsrCounter & 0x1FFF) > 0x0FFF)

        {
            flip();  // Toggle Green LED
        }
   
    } 
       
}

