#ifndef _OPIZ_PWM_H_
#define _OPIZ_PWM_H_

typedef enum
{
	PRESCALE_DIV120 = 0x00,  /* Divide 24mhz clock by 120 */
	PRESCALE_DIV180 = 0x01,
	PRESCALE_DIV240 = 0x02,
	PRESCALE_DIV360 = 0x03,
	PRESCALE_DIV480 = 0x04,
	PRESCALE_DIV12k = 0x08,
	PRESCALE_DIV24k = 0x09,
	PRESCALE_DIV36k = 0x0a,
	PRESCALE_DIV48k = 0x0b,
	PRESCALE_DIV72k = 0x0c,
	PRESCALE_DIV_NO = 0x0f
} pwm_prescale;

extern int opiz_pwm_init(); 
extern int opiz_pwm_enable();
extern int opiz_pwm_disable();
extern int opiz_pwm_set_polarity(unsigned int value);
extern unsigned int opiz_pwm_get_polarity();   
extern int opiz_pwm_set_prescale(pwm_prescale value);
extern pwm_prescale opiz_pwm_get_prescale();
extern int opiz_pwm_set_entirecycles(unsigned short value);
extern unsigned short opiz_pwm_get_entirecycles(); 
extern int opiz_pwm_set_activecycles(unsigned short value);
extern unsigned short opiz_pwm_get_activecycles(); 

#endif // _OPIZ_PWM_H_