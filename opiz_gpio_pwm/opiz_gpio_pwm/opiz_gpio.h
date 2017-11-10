#ifndef _OPIZ_GPIO_H_
#define _OPIZ_GPIO_H_

#define SW_PORTC_IO_BASE 0x01c20800


#define OPIZ_GPIO_A	0
#define OPIZ_GPIO_B	1
#define OPIZ_GPIO_C	2
#define OPIZ_GPIO_D	3
#define OPIZ_GPIO_E	4
#define OPIZ_GPIO_F	5
#define OPIZ_GPIO_G	6
#define OPIZ_GPIO_H	7
#define OPIZ_GPIO_I		8
#define OPIZ_GPIO_J	9
#define OPIZ_GPIO_K	10
#define OPIZ_GPIO_L	11
#define OPIZ_GPIO_M	12
#define OPIZ_GPIO_N	13
#define OPIZ_GPIO_O	14


struct opiz_gpio {
    unsigned int cfg[4];
    unsigned int dat;
    unsigned int drv[2];
    unsigned int pull[2];
};

/* gpio interrupt control */
struct opiz_gpio_int {
    unsigned int cfg[3];
    unsigned int ctl;
    unsigned int sta;
    unsigned int deb;
};

struct opiz_gpio_reg {
    struct opiz_gpio gpio_bank[9];
    unsigned char res[0xbc];
    struct opiz_gpio_int gpio_int;
};

#define GPIO_BANK(pin)	((pin) >> 5)
#define GPIO_NUM(pin)	((pin) & 0x1F)

#define GPIO_CFG_INDEX(pin)	(((pin) & 0x1F) >> 3)
#define GPIO_CFG_OFFSET(pin)	((((pin) & 0x1F) & 0x7) << 2)

#define GPIO_PUL_INDEX(pin)	(((pin) & 0x1F )>> 4) 
#define GPIO_PUL_OFFSET(pin)	(((pin) & 0x0F) << 1)

/* GPIO bank sizes */
#define OPIZ_GPIO_A_NR		(32)
#define OPIZ_GPIO_B_NR		(32)
#define OPIZ_GPIO_C_NR		(32)
#define OPIZ_GPIO_D_NR		(32)
#define OPIZ_GPIO_E_NR		(32)
#define OPIZ_GPIO_F_NR		(32)
#define OPIZ_GPIO_G_NR		(32)
//BY CHOW add
#define OPIZ_GPIO_H_NR		(32)
#define OPIZ_GPIO_I_NR		(32)
#define OPIZ_GPIO_J_NR		(32)
#define OPIZ_GPIO_K_NR		(32)
#define OPIZ_GPIO_L_NR		(32)
#define OPIZ_GPIO_M_NR		(32)
#define OPIZ_GPIO_N_NR		(32)
#define OPIZ_GPIO_O_NR		(32)
//


#define OPIZ_GPIO_NEXT(__gpio) ((__gpio##_START)+(__gpio##_NR)+0)

enum opiz_gpio_number {
    OPIZ_GPIO_A_START = 0,
    OPIZ_GPIO_B_START = OPIZ_GPIO_NEXT(OPIZ_GPIO_A), //32
    OPIZ_GPIO_C_START = OPIZ_GPIO_NEXT(OPIZ_GPIO_B), //64
    OPIZ_GPIO_D_START = OPIZ_GPIO_NEXT(OPIZ_GPIO_C), //96
    OPIZ_GPIO_E_START = OPIZ_GPIO_NEXT(OPIZ_GPIO_D), //128
    OPIZ_GPIO_F_START = OPIZ_GPIO_NEXT(OPIZ_GPIO_E), //160
    OPIZ_GPIO_G_START = OPIZ_GPIO_NEXT(OPIZ_GPIO_F), //192
// BY CHOW  ADD
    OPIZ_GPIO_H_START = OPIZ_GPIO_NEXT(OPIZ_GPIO_G), //224	
    OPIZ_GPIO_I_START = OPIZ_GPIO_NEXT(OPIZ_GPIO_H), //256
   OPIZ_GPIO_J_START = OPIZ_GPIO_NEXT(OPIZ_GPIO_I), //288	
    OPIZ_GPIO_K_START = OPIZ_GPIO_NEXT(OPIZ_GPIO_J), //320
    OPIZ_GPIO_L_START = OPIZ_GPIO_NEXT(OPIZ_GPIO_K), //352
    OPIZ_GPIO_M_START = OPIZ_GPIO_NEXT(OPIZ_GPIO_L), //384
    OPIZ_GPIO_N_START = OPIZ_GPIO_NEXT(OPIZ_GPIO_M), //448
    OPIZ_GPIO_O_START = OPIZ_GPIO_NEXT(OPIZ_GPIO_N), //448+32


};

/* SUNXI GPIO number definitions */
#define OPIZ_GPA(_nr) (OPIZ_GPIO_A_START + (_nr))
#define OPIZ_GPB(_nr) (OPIZ_GPIO_B_START + (_nr))
#define OPIZ_GPC(_nr) (OPIZ_GPIO_C_START + (_nr))
#define OPIZ_GPD(_nr) (OPIZ_GPIO_D_START + (_nr))
#define OPIZ_GPE(_nr) (OPIZ_GPIO_E_START + (_nr))
#define OPIZ_GPF(_nr) (OPIZ_GPIO_F_START + (_nr))
#define OPIZ_GPG(_nr) (OPIZ_GPIO_G_START + (_nr))
#define OPIZ_GPH(_nr) (OPIZ_GPIO_H_START + (_nr))
#define OPIZ_GPI(_nr) (OPIZ_GPIO_I_START + (_nr))
//add by chow
#define OPIZ_GPJ(_nr) (OPIZ_GPIO_J_START + (_nr))
#define OPIZ_GPK(_nr) (OPIZ_GPIO_K_START + (_nr))
#define OPIZ_GPL(_nr) (OPIZ_GPIO_L_START + (_nr))
#define OPIZ_GPM(_nr) (OPIZ_GPIO_M_START + (_nr))
#define OPIZ_GPN(_nr) (OPIZ_GPIO_N_START + (_nr))
#define OPIZ_GPO(_nr) (OPIZ_GPIO_O_START + (_nr))



/* GPIO pin function config */
#define OPIZ_GPIO_INPUT (0)
#define OPIZ_GPIO_OUTPUT (1)
#define OPIZ_GPIO_PER (2)

#define OPIZ_PULL_NONE (0)
#define OPIZ_PULL_UP (1)
#define OPIZ_PULL_DOWN (2)

extern int opiz_gpio_input(unsigned int pin);
extern int opiz_gpio_init(void);
extern int opiz_gpio_set_cfgpin(unsigned int pin, unsigned int val);
extern int opiz_gpio_get_cfgpin(unsigned int pin);
extern int opiz_gpio_output(unsigned int pin, unsigned int val);
extern int opiz_gpio_pullup(unsigned int pin, unsigned int pull);


extern unsigned int OPIZ_PIO_BASE;
#endif // _OPIZ_GPIO_H_ 
