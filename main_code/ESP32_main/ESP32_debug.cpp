/*------------------------------------------------------------*-
  debug - function file
  ESP32 DEVKIT V1
  (c) Can Tho University - 2019
  version 1.00 - 23/10/2019
---------------------------------------------------------------
 * ESP-IDF version: 3.2
 * Compiler version: 5.2.0
 * Arduino components version: latest
--------------------------------------------------------------*/
#ifndef  __ESP32_DEBUG_CPP
#define  __ESP32_DEBUG_CPP
#include "ESP32_debug.h"


#define PUBLISH_PERIOD_MS       10000
// ------ Private constants -----------------------------------

// ------ Private function prototypes -------------------------

// ------ Private variables -----------------------------------
uint64_t last_pub_time = 0;

// ------ PUBLIC variable definitions -------------------------

//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
void debug_init() {
  vSemaphoreCreateBinary(baton); //initialize binary semaphore //baton = xSemaphoreCreateBinary(); //this works too but not as good as the current use

  UART_init();
  ADC_init();
  PID_init();
  pump1_init();
  pump2_init();
  relay_init();
  FlowSensor_init();
  UART_masterReady();
  core0_init(); //must stand above MQTT init
  
  xSemaphoreTake(baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
  xSemaphoreGive(baton);

}//end debug_init
//------------------------------------------------------------
void system_debug() {
  uint64_t time_since_last_pub = millis() - last_pub_time;
  if (time_since_last_pub >= PUBLISH_PERIOD_MS)
  {
//  PUBLISH THE TEMPERATURE LIKE THIS
  MQTT_T1_pub(tempSen01_read());
  MQTT_T2_pub(tempSen02_read());
  MQTT_T3_pub(tempSen03_read());
  MQTT_T4_pub(tempSen04_read());

//  PUBLISH THE PUMP PWM FREQ LIKE THIS
  MQTT_Pump1pwm_pub(pump1pwm_read());
  MQTT_FlowSen_01_pub(FlowSensor_get_flow_polling());
  // MQTT_Pump2pwm_pub(pump2pwm_read());
  last_pub_time = millis();
  }

}//end system_debug

#endif // __ESP32_DEBUG_CPP
