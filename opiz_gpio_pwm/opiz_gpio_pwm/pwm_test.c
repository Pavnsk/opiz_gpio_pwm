#include "opiz_gpio.h"
#include "opiz_pwm.h"

int main()
{
	opiz_gpio_init();	
	opiz_gpio_set_cfgpin(OPIZ_GPA(6), 3);
	opiz_pwm_init();
	opiz_pwm_enable();
	opiz_pwm_set_entirecycles(100);
	opiz_pwm_set_activecycles(10);
	return 0;
}