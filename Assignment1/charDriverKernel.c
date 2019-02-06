#include<linux/init.h>
#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/kdev_t.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/device.h>
#include <linux/types.h>
#include <linux/random.h>
#include <linux/uaccess.h>

static struct cdev* c_dev;
static dev_t device_number;
static struct class *cls;
dev_t x_axis,y_axis,z_axis,first;
uint16_t value;

static int permission(struct device* dev,struct kobj_uevent_env* env)
{
  add_uevent_var(env,"DEVMODE=%#o",0666);
  return 0;
}


static int my_open(struct inode *i,struct file *f)
{
printk(KERN_INFO "open()\n");
return 0;
}


static int my_close(struct inode *i,struct file *f)
{
printk(KERN_INFO "close()\n");
return 0;
}


static ssize_t my_read(struct file *f,char __user *buf,size_t len,loff_t *off)
{
uint16_t i;
get_random_bytes(&i, sizeof(i));
value=i&0x03FF;
copy_to_user(buf, &value, sizeof(i));
printk(KERN_INFO "%d\n",value);
printk(KERN_INFO "read()\n");
return 0;
}





static struct file_operations fops =
{
.owner=THIS_MODULE,
.open=my_open,
.release=my_close,
.read=my_read,
};



static __init int demo_init(void)
{
	printk(KERN_INFO "Accelerometer registered\n\n");
	if((alloc_chrdev_region(&device_number,0,3,"accelerometer"))<0) 
		{
			return -1;
		}
	x_axis=MKDEV(MAJOR(device_number), MINOR(device_number)+0);
	y_axis=MKDEV(MAJOR(device_number), MINOR(device_number)+1);
	z_axis=MKDEV(MAJOR(device_number), MINOR(device_number)+2);
	if((cls=class_create(THIS_MODULE,"adxl"))==NULL)
		{
			unregister_chrdev_region(device_number,3);
			return -1;
		}
cls->dev_uevent = permission;
	
	device_create(cls,NULL,x_axis,NULL,"adxl_x");
	device_create(cls,NULL,y_axis,NULL,"adxl_y");
	device_create(cls,NULL,z_axis,NULL,"adxl_z");
        c_dev=cdev_alloc();
	cdev_init(c_dev,&fops);
	cdev_add(c_dev,device_number,3);
	return 0;

}


static __exit void demo_exit(void)
{
cdev_del(c_dev);
device_destroy(cls,x_axis);
device_destroy(cls,y_axis);
device_destroy(cls,z_axis);
class_destroy(cls);
unregister_chrdev_region(device_number,3);
printk(KERN_INFO "Accelerometer unregistered\n\n");
}

module_init(demo_init);
module_exit(demo_exit);

MODULE_DESCRIPTION("Assignment_1 - 3 axis Accelerometer Device Driver");
MODULE_AUTHOR("Likhith V");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
