#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>

#include "opiz_pwm.h"

#define OPIZ_PWM_BASE 0x01c21400


#define OPIZ_PWM_CH0_CTRL 0x10
#define OPIZ_PWM_CH0_PERIOD 0x14


typedef struct
{
   pwm_prescale prescalar:4;
   unsigned int enable:1;
   unsigned int active_state:1;
   unsigned int gating:1;
   unsigned int mode:1;
   unsigned int pulse_start:1;
   unsigned int bypass:1;
   unsigned int unused0:18;
   unsigned int period_reg_ready:1;
   unsigned int unused1:3;
} pwm_ctrl_reg;

typedef struct
{
	unsigned short active_cycles : 16;
	unsigned short entire_cycles : 16;
} pwm_period_reg;

volatile pwm_ctrl_reg *ctrl_reg_ptr = 0;
volatile pwm_period_reg *period_reg_ptr = 0;

int opiz_pwm_init()
{   
	unsigned int pwm_base_ptr = 0;

	int fd;
	unsigned int addr_start, addr_offset;
	unsigned int page_size, page_mask;
	void *pc;

	fd = open("/dev/mem", O_RDWR);
	if (fd < 0) {
		return (-1);
	}
	
	page_size = sysconf(_SC_PAGESIZE);
	page_mask = (~(page_size - 1));

	addr_start = OPIZ_PWM_BASE & page_mask;
	addr_offset = OPIZ_PWM_BASE & ~page_mask;

	pc = (void *)mmap(0, page_size * 2, PROT_READ | PROT_WRITE, MAP_SHARED, fd, addr_start);
	if (pc == MAP_FAILED) {
		return (-1);
	}

	pwm_base_ptr = (unsigned int)pc;
	pwm_base_ptr += addr_offset;

	ctrl_reg_ptr = pwm_base_ptr + OPIZ_PWM_CH0_CTRL;
	period_reg_ptr = pwm_base_ptr + OPIZ_PWM_CH0_PERIOD;

	close(fd);
	return 0;
}

int opiz_pwm_enable()
{
	pwm_ctrl_reg ctrl_data = *ctrl_reg_ptr;
	ctrl_data.enable = 1;
	ctrl_data.active_state = 1;
	ctrl_data.gating = 1;
	ctrl_data.mode = 0;
	ctrl_data.prescalar = PRESCALE_DIV240;
	*ctrl_reg_ptr = ctrl_data;    
	pwm_period_reg pwm_period_data;
	pwm_period_data.active_cycles = 1;
	pwm_period_data.entire_cycles = 1;
	do 	{
		ctrl_data = *ctrl_reg_ptr;
	} while (ctrl_data.period_reg_ready);
	(*period_reg_ptr) = pwm_period_data;
	return 0;
}

int opiz_pwm_disable()
{
	(*ctrl_reg_ptr).enable = 0;
    return 0;
}

int opiz_pwm_set_polarity(unsigned int value)
{
	if (value > 0)
		(*ctrl_reg_ptr).active_state = 1;
	else
		(*ctrl_reg_ptr).active_state = 0;
	return 0;
}

unsigned int opiz_pwm_get_polarity()
{
    return (*ctrl_reg_ptr).active_state;
}

int opiz_pwm_set_prescale(pwm_prescale value)
{
	(*ctrl_reg_ptr).prescalar = value;
    return 0;
}

pwm_prescale opiz_pwm_get_prescale()
{
    return (*ctrl_reg_ptr).prescalar;
}

int opiz_pwm_set_entirecycles(unsigned short value)
{
	pwm_ctrl_reg ctrl_data;
	pwm_period_reg pwm_period_data = *period_reg_ptr;	
	pwm_period_data.entire_cycles = value;
	do {
		ctrl_data = *ctrl_reg_ptr;
	} while (ctrl_data.period_reg_ready);
	(*period_reg_ptr) = pwm_period_data;
	return 0;
}

unsigned short opiz_pwm_get_entirecycles()
{	
	return (*period_reg_ptr).entire_cycles;
}

int opiz_pwm_set_activecycles(unsigned short value)
{
	pwm_ctrl_reg ctrl_data;
	pwm_period_reg pwm_period_data = *period_reg_ptr;
	pwm_period_data.active_cycles = value;
	do {
		ctrl_data = *ctrl_reg_ptr;
	} while (ctrl_data.period_reg_ready);
	(*period_reg_ptr) = pwm_period_data;
	return 0;
}

unsigned short opiz_pwm_get_activecycles()
{
    return (*period_reg_ptr).active_cycles;
}

 
