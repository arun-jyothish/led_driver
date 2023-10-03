/*
 * Arun jyothish k
 *
 * simply turn ON and OFF ... blue LED , add-on board
*/


#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/io.h>

MODULE_DESCRIPTION("LED DRIVER TURNS OFF THE GPIO LED (BLUE)");
MODULE_AUTHOR("Arun jyothish k.");
MODULE_LICENSE("GPL");

static void __iomem*		gpio_b_dr_vm  ;
static void __iomem*		gpio_b_psr_vm ;
static void __iomem*		gpio_b_gdir_vm;

static void led_off(void);
static void led_on(void);
static void setup (void);

#define	gpio_b_base_addr	(0x20A4000)

#define		gpio_b_dr			gpio_b_base_addr
#define		gpio_b_psr			(gpio_b_base_addr+0x08)
#define		gpio_b_gdir			(gpio_b_base_addr+0x04)


#define 	led_blue_pin		(26)
#define 	button_pin		27


static int  __init led_driver_init(void){
	printk(KERN_INFO "led_driver module Loaded....");
	printk(KERN_INFO "dr: %u, gdir: %u",gpio_b_dr,gpio_b_gdir);

gpio_b_dr_vm	= ioremap(gpio_b_dr, sizeof(u32))	;
gpio_b_psr_vm	= ioremap(gpio_b_psr, sizeof(u32));	
gpio_b_gdir_vm	= ioremap(gpio_b_gdir, sizeof(u32));

	setup();
	led_off();
	return 0;
}

static void __exit led_driver_exit(void){
	led_on();
	iounmap(gpio_b_dr_vm);
	iounmap(gpio_b_gdir_vm);
	iounmap(gpio_b_psr_vm);
	printk(KERN_INFO "LED DR exit....");
}


static void setup (void){

#define mask_pin 0b1 << led_blue_pin
		 /* iowrite32( 67108864 , gpio_b_gdir_vm);		// sets led pin as output */
		 /* iowrite32(0b0 << button_pin , gpio_b_gdir_vm);		// sets button pin as input */
											//
		 u32 read  = ioread32(gpio_b_gdir_vm);		//  
		 /* printk(KERN_INFO "gdir gp3: %x",mask_pin); */
		 printk(KERN_INFO "reg val: %x",read);

		 iowrite32( mask_pin , gpio_b_gdir_vm);		// sets led pin as output
		 read  = ioread32(gpio_b_gdir_vm);		//  
		 printk(KERN_INFO "reg val: %x",read);
}

static void led_on(void){
		  iowrite32( 0b1 << led_blue_pin, gpio_b_dr_vm);		// turn on led 
}

static void led_off(void){
		  iowrite32( 0b0 << led_blue_pin, gpio_b_dr_vm);		// turn off led 
}

module_init(led_driver_init);
module_exit(led_driver_exit);
