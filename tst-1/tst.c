/*
 * This is a demo Linux kernel module.
 */

#include <linux/miscdevice.h>
#include <linux/delay.h>
#include <asm/irq.h>
#include <mach/regs-gpio.h>
#include <mach/hardware.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/string.h>
#include <linux/list.h>
#include <linux/pci.h>
#include <linux/gpio.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>
#include <asm/unistd.h>

#define DEVICE_NAME "gpb5"

static int sbc2440_gpb5_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg) 
{ 
	printk("in krnl:%d - %d \n",cmd,arg);
	switch(cmd) 
		{ 
			case 1: 
			case 0: 
				s3c2410_gpio_setpin(S3C2410_GPB(5), !cmd);
				return 0; 			
			default: 
				return -EINVAL; 
		} 
}

static struct file_operations dev_fops = { 
	.owner = THIS_MODULE, 
	.unlocked_ioctl = sbc2440_gpb5_ioctl, 
};
static struct miscdevice misc = { 
	.minor = MISC_DYNAMIC_MINOR, 
	.name = DEVICE_NAME, 
	.fops = &dev_fops, 
};


/*
 * template_init - function to insert this module into kernel space
 *
 * This is the first of two exported functions to handle inserting this
 * code into a running kernel
 *
 * Returns 0 if successfull, otherwise -1
 */

static int __init template_init(void)
{
	int ret;
	s3c2410_gpio_cfgpin(S3C2410_GPB(5), S3C2410_GPIO_OUTPUT); 
	s3c2410_gpio_setpin(S3C2410_GPB(5), 1); 
	ret = misc_register(&misc);
	printk (DEVICE_NAME"\tinitialized\n");

	printk("Module init done!\n");
	return ret;
}

/*
 * template_cleanup - function to cleanup this module from kernel space
 *
 * This is the second of two exported functions to handle cleanup this
 * code from a running kernel
 */

static void __exit template_cleanup(void)
{
	 misc_deregister(&misc);
	 printk("MOdule Cleaned-up!\n");
}

module_init(template_init);
module_exit(template_cleanup);

MODULE_DESCRIPTION("My First Kernel driver!! :)");
MODULE_LICENSE("GPL");

