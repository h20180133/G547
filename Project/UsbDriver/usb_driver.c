#include <linux/usb.h>// for usb_contro_msg
#include <linux/init.h>// macros used to markup functions e.g. __init, __exit
#include <linux/module.h>// Core header for loading LKMs into the kernel
#include <linux/kernel.h>// Contains types, macros, functions for the kernel
#include <linux/device.h>// Header to support the kernel Driver Model
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/delay.h>//mdelay function
#include "commands.h"

static struct usb_device *device;  
static struct usb_class_driver class;

   
static int adc_open(struct inode *i,struct file *f)
{
	printk(KERN_INFO"ADC file Opened\n");    
	return 0;
}
static int adc_close(struct inode *i,struct file *f)
{
	printk(KERN_INFO"ADC file Closed\n");  
    return 0;
}





static long adc_ioctl(struct file *f,unsigned int cmd,unsigned long arg)    //IOCTL callback
{
int a;
printk(KERN_INFO"Inside IOCTL\n");
printk(KERN_INFO"cmd = %u arg = %lu\n",cmd,arg);
switch(cmd)
	{

		case THRESHOLD:			
			printk(KERN_INFO"Sending to USB\n");
            		a=usb_control_msg(device,usb_sndctrlpipe(device,0),0x01,USB_TYPE_VENDOR|USB_DIR_OUT,arg,0,0,0,0);  //use usb_control_msg to send threshold value to atmega8
			printk(KERN_INFO"a=%d\n",a);			
			break;
		
		default:
			printk(KERN_INFO"Invalid Command\n");




	}



return 0;
}





static struct file_operations fops =    //Callback functions for the device file
{
    .owner=THIS_MODULE,
    .open=adc_open,
    .release=adc_close,
    .unlocked_ioctl=adc_ioctl,
};


static struct usb_device_id my_id_table[]=
{

	{USB_DEVICE(0x16C0,0x05DC)},
	{}


};

MODULE_DEVICE_TABLE(usb,my_id_table);

static int my_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
int status;
device = interface_to_usbdev(interface);
printk(KERN_INFO "USB ADC with VID=%04X PID=%04X Found\n",id->idVendor,id->idProduct);
class.name="usb/myadc";				
class.fops=&fops;
 if((status=usb_register_dev(interface,&class))<0) /* driver registration (hot plugging) */
    {
      printk(KERN_ERR "USB ADC Sensor Driver FAIL\n");
    
    }
    else
    {
        printk(KERN_INFO "USB ADC Sensor Driver ON, Minor = %d\n",interface->minor);
	
    }


return status;
}


static void my_disconnect(struct usb_interface *interface)
{
 usb_deregister_dev(interface,&class); /* dynamic driver deregistration */
printk(KERN_INFO "USB ADC Removed");

}


static struct usb_driver mydriver=  //Callback functions for usb driver
{

	.name="MyUSBDriver",
	.id_table=my_id_table,
	.probe=my_probe,
	.disconnect=my_disconnect,

};

static  __init int mydriver_init(void)
{

int ret;
ret=usb_register(&mydriver);   //register usb driver with usb core

return 0;
}

static __exit void mydriver_exit(void)
{

usb_deregister(&mydriver); //deregister usb driver from usb core


}




module_init(mydriver_init);
module_exit(mydriver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Likhith V");
MODULE_DESCRIPTION("Sending Threshold value of a sensor via USB protocol");
