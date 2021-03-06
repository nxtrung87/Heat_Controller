/*-------------------------------------------
  UART - header file
  ARDUINO NANO
  (c) Can Tho University 2019 
  version 1.10 - 25/08/2019
----------------------------------------------
 * All test function used with UART to USB has
 * to be in "No line ending" mode
--------------------------------------------*/
#ifndef  __NANO_UART_H 
#define  __NANO_UART_H
#include <Arduino.h>
#include "Nano_SD.h"
#include "Nano_LCD.h"
#include "debugConfig.h"
//#include "config.h"

// ------ Public constants ------------------------------------
#define AUTHORIZED_KEY "master ready! 070497"
// ------ Public function prototypes --------------------------
/**
Initialize UART
**/
void UART_init();
/**
confirm from UART that master is ready or not
**/
void UART_isMasterReady();
/**
Collect the data from serial port if existed and send to SD
**/
void UART_getFromMaster();
/**
Send PID data to master
**/
void PIDsendToMaster(float*);
/**
Send temperature data to master
**/
void sTempSendToMaster(uint16_t*);
/**
Send flow data to master
**/
void sFlowSendToMaster(float*);
// ------ Public variable -------------------------------------

#endif // __NANO_UART_H
