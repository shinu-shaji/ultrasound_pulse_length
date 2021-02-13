#ifndef PULSELNLIB_H
#define PULSELNLIB_H
    #define timer_load_value  0xfffff
    #define pinio_1 16
    static xQueueHandle pulse_length=NULL;
    //uint16_t pulse_lenght=0;
    
    typedef struct {
        int pin_no;
        int32_t pin_mask;
    }pulse_ln_conf;

    pulse_ln_conf pulse_ln;

    void end_timer_callback();
    void set_timer();
    void timer_callback();
    void conf_gpio_pins();
    void pulseln();

#endif