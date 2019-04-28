obj-m:=usb_driver.o
 
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

insert: usb_driver.ko
	sudo insmod usb_driver.ko

remove: usb_driver.ko
	sudo rmmod usb_driver

clean:
	rm -rf *.o *.order *.ko *.mod *.symvers *.mod.c


