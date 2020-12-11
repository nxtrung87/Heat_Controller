#ifndef _ESP32_FLOWSENSOR_H
#define _ESP32_FLOWSENSOR_H

#define PCNT_FLOWSENSOR_UNIT        PCNT_UNIT_0
#define PCNT_H_LIM_VAL              1000
#define PCNT_L_LIM_VAL              -1000
#define PCNT_THRESH1_VAL            5
#define PCNT_THRESH0_VAL            -5
#define PCNT_INPUT_SIG_IO           14  // Pulse Input GPIO
#define PCNT_INPUT_CTRL_IO          PCNT_PIN_NOT_USED

#define TIMER_DIVIDER               80
#define TIMER_SCALE                 (TIMER_BASE_CLK / TIMER_DIVIDER / 1000)  // convert counter value to milliseconds
#define FLOWSENSOR_READ_PERIOD_MS   1000
#define NR_MS_IN_SEC                1000
#define NR_SEC_IN_MINUTE            60

#define FLOWSENSOR_K_FACTOR         1420

/** @brief Initialize Flow Sensor measurement
 */
void FlowSensor_init(void);

/** @brief Get the current Flow Sensor value
 * @return The current Flow Sensor value
 */
float FlowSensor_get_flow();

/** @brief Start Flow Sensor measurement
 */
void FlowSensor_start();

/** @brief Pause Flow Sensor measurement
 */
void FlowSensor_pause();

/** @brief Get the current Flow Sensor value in a polled manner
 * @return The current Flow Sensor value
 */
float FlowSensor_get_flow_polling();

#endif //_ESP32_FLOWSENSOR_H