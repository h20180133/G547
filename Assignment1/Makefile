obj-m:=charDriverKernel.o
 
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

insert: charDriverKernel.ko
	sudo insmod charDriverKernel.ko

remove: charDriverKernel.ko
	sudo rmmod charDriverKernel


compile:userapplication.c
	gcc userapplication.c -o userapplication

app:
	./userapplication

clean:
	rm -rf *.o *.order *.ko *.mod *.symvers *.mod.c


