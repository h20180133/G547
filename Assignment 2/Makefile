obj-m:=main.o
 
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	rm -rf *.o *.order *.ko *.mod *.symvers *.mod.c


