/*------------------------------------------------------------*-
  MAIN - functions file
  ESP32 DEVKIT V1
  (c) Can Tho University - 2019
  version 1.00 - 14/08/2019
---------------------------------------------------------------
 * ESP-IDF version: 3.2
 * Compiler version: 5.2.0
 * Arduino components version: latest
--------------------------------------------------------------*/





#ifdef SYSTEM_DEBUG
  
#else
#include "ESP32_debug.h"
#include "ESP32_stateFlow.h"
#include "ESP32_MQTT.h"
#endif


///////////////////////////////////////MAIN FUNCTION/////////////////////////////////////
// ---------------------------------- SETUP PROTOCOL -------------------------------------------
void setup() {
    
  #ifdef SYSTEM_DEBUG
    debug_init();
  #else
    System_init();
  #endif

}// end setup
// ---------------------------------- LOOP -------------------------------------------
void loop() {

  #ifdef SYSTEM_DEBUG
  #else
    MQTT_loopHandle();
    MQTT_subscribeInit();
    system_debug();
    MQTT_maintain();
    MQTT_subscribe();
  #endif
  
}//end loop
