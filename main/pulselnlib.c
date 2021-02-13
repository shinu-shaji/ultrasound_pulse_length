
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "pulselnlib.h"
#include "esp_log.h"

#include "driver/gpio.h"
#include "driver/hw_timer.h"



/*
interrupt = any edge

*/
// define pin number for pulse_ln sensor



void end_timer_callback(){
    int a =NULL;
};

//set timer function
void set_timer(){
    printf("stting timer");
    hw_timer_init(end_timer_callback,NULL);
    hw_timer_set_load_data(timer_load_value);

}

//timer callback function
void timer_callback(){
    static bool en = 1;
    //xQueueSendFromISR(pulse_length,&en,NULL);
    hw_timer_enable(en);
    
    if(!en){
        uint16_t data = hw_timer_get_count_data();
        xQueueSendFromISR(pulse_length,&data,NULL);
        en = 1;
    }
    else{
        en = !en;
    }
    
}

void conf_gpio_pins(){
    //pulse_ln.pin_mask = (1<<pulse_ln.pin_no);
    gpio_config_t io_conf;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.intr_type =GPIO_INTR_ANYEDGE;
    io_conf.pin_bit_mask = (1<<pulse_ln.pin_no);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    gpio_install_isr_service(0);
    set_timer();
    gpio_isr_handler_add(pulse_ln.pin_no,timer_callback,NULL);
}




void pulseln(){
    //pin configuration
    //set_timer();
    conf_gpio_pins();
    int pulse_ln_data=NULL;
    pulse_length = xQueueCreate(2,sizeof(int16_t));
    while(1){
        printf("waiting");
       // printf("%d\n",hw_timer_get_count_data());
        
        if(xQueueReceive(pulse_length,&pulse_ln_data,portMAX_DELAY)){
            printf("testpoint 1");
            
          //  gpio_isr_handler_remove(pulse_ln.pin_no);
            printf("%d\n",pulse_ln_data);
            
           // return pulse_ln_data;
        }
    }


}