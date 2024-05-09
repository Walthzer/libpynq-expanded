 /*
 *  TU/e 5EID0::LIBPYNQ Example for PULSECOUNTER
 *
 *  Interface:
 *  Button 0: Increment count
 * 
 *  Written By: Walthzer
 * 
 */

#include <stdio.h>
#include <libpynq.h>
#define AS_SECONDS(time) (time / 1.0e8) //Timer runs at ~100MHZ

int main()
{
    pynq_init();
    switchbox_set_pin(IO_BTN0, SWB_TIMER_IC0); //Pulsecounter 0 to Button 0
    pulsecounter_init(PULSECOUNTER0);

    //Use Rising edge triggering
    pulsecounter_set_edge(PULSECOUNTER0, GPIO_LEVEL_HIGH);
    pulsecounter_reset_count(PULSECOUNTER0);

    uint32_t past_count = 0;
    uint32_t past_time = 0;
    while(1)
    {
        uint32_t time;
        uint32_t count = pulsecounter_get_count(PULSECOUNTER0, &time);

        if(past_time == 0)
            past_time = time;

        if(count != past_count)
        {
            uint32_t delta = time - past_time; //unsigned arithmetic negates wrapping.
            printf("Count: %u -- Time delta: %f\n", count, AS_SECONDS(delta));

            past_time = time;
            past_count = count;
        }
    }
    
    pulsecounter_destroy(PULSECOUNTER0);
    pynq_destroy();
    return 0;
}