#include "ESP32_FlowSensor.h"
#include "esp_types.h"
#include "driver/pcnt.h"


/* Prepare configuration for the PCNT unit */
pcnt_config_t pcnt_config = {
    // Set PCNT input signal and control GPIOs
    .pulse_gpio_num = PCNT_INPUT_SIG_IO,
    .ctrl_gpio_num = PCNT_INPUT_CTRL_IO,
    // What to do when control input is low or high?
    .lctrl_mode = PCNT_MODE_DISABLE, // Disable counting if low
    .hctrl_mode = PCNT_MODE_KEEP,    // Keep the primary counter mode if high
    // What to do on the positive / negative edge of pulse input?
    .pos_mode = PCNT_COUNT_INC,   // Count up on the positive edge
    .neg_mode = PCNT_COUNT_DIS,   // Keep the counter value on the negative edge        
    // Set the maximum and minimum limit values to watch
    .counter_h_lim = PCNT_H_LIM_VAL,
    .counter_l_lim = PCNT_L_LIM_VAL,
    .unit = PCNT_UNIT_0,
    .channel = PCNT_CHANNEL_0,
};

timer_config_t timer_config = {
    .alarm_en = TIMER_ALARM_EN,      /*!< Timer alarm enable */
    .counter_en = TIMER_PAUSE,    /*!< Counter disable */
    .intr_type = TIMER_INTR_LEVEL, /*!< Interrupt mode */
    .counter_dir = TIMER_COUNT_UP, /*!< Counter direction  */
    .auto_reload = TIMER_AUTORELOAD_DIS,   /*!< Timer auto-reload */
    .divider =  TIMER_DIVIDER,  /*!< Counter clock divider. The divider's range is from from 2 to 65536. */
};

int16_t flowsensor_current_count = 0;
float flowsensor_current_flow = 0;

void FlowSensor_timer_isr(void * param);
void FlowSensor_calc_flow();

void FlowSensor_init()
{
 
    /* Initialize PCNT unit */
    pcnt_unit_config(&pcnt_config);

    /* Configure and enable the input filter */
    pcnt_set_filter_value(PCNT_FLOWSENSOR_UNIT, 8);
    pcnt_filter_enable(PCNT_FLOWSENSOR_UNIT);

    /* Initialize PCNT's counter */
    pcnt_counter_pause(PCNT_FLOWSENSOR_UNIT);
    pcnt_counter_clear(PCNT_FLOWSENSOR_UNIT);

    /* Initialize Timer unit */
    timer_init(TIMER_GROUP_0, TIMER_0, &timer_config);

    /* Configure the alarm value and the interrupt on alarm. */
    timer_set_alarm_value(TIMER_GROUP_0, TIMER_0, FLOWSENSOR_READ_PERIOD_MS * TIMER_SCALE);
    timer_enable_intr(TIMER_GROUP_0, TIMER_0);
    timer_isr_register(TIMER_GROUP_0, TIMER_0, FlowSensor_timer_isr,
                    (void *)NULL, ESP_INTR_FLAG_LEVEL1, NULL);
}

void FlowSensor_start()
{
    timer_start(TIMER_GROUP_0, TIMER_0);
    pcnt_counter_resume(PCNT_FLOWSENSOR_UNIT);
}

void FlowSensor_pause()
{
    timer_pause(TIMER_GROUP_0, TIMER_0);
    pcnt_counter_pause(PCNT_FLOWSENSOR_UNIT);
}


void FlowSensor_timer_isr(void * param)
{
    pcnt_counter_pause(PCNT_FLOWSENSOR_UNIT);
    pcnt_get_counter_value(PCNT_FLOWSENSOR_UNIT, &flowsensor_current_count);
    FlowSensor_calc_flow();
    pcnt_counter_resume(PCNT_FLOWSENSOR_UNIT);
}

void FlowSensor_calc_flow()
{
    flowsensor_current_flow = flowsensor_current_count * NR_MS_IN_SEC/FLOWSENSOR_READ_PERIOD_MS
                                * NR_SEC_IN_MINUTE / FLOWSENSOR_K_FACTOR;
}

float FlowSensor_get_flow()
{
    return flowsensor_current_flow;
}