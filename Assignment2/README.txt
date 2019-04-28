1. Build the driver by executing below command in terminal
$ make

2. Insert the driver module into kernel by executing below command
$ sudo insmod main.ko

3. Check the device size and partitions' size by executing below command

$ sudo fdisk -l /dev/rb

It will display device size, number of sectors, sector size and details of two primary partitions rb1 and rb2.


4. Write to block device by executing below commands

$ sudo su

# cat > /dev/rb1
"Data to be written"

5. See the written data into block device by executing below command.

# xxd /dev/rb1 | less

6. Read from a block device

# dd if=/dev/rb of=/dev/null bs=512 count=1024

# dmesg -wH

It can be seen in kernel log the data is read sector wise from block device.
