#include <stdio.h> 
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <ctype.h>


int main()
{ 
  int fd;
  char s;
  uint16_t value;  
 
do{
printf("\nPress x for x-axis data, y for y-axis data, z for z axis data..Press e to exit\n");
scanf(" %c",&s);

switch(tolower(s))
	{

case 'x': 	
		fd=open("/dev/adxl_x", O_RDWR);
		if(fd  == -1)
  		{  
    			printf("Please give the necessary permissions for device file in /dev/adxl_x\n");
    			exit(-1);
  		}
  
  		read(fd,&value,2);

  		printf("Accelerometer x_axis value is %d\n",value);
		printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		break;
		

case 'y': 
		fd=open("/dev/adxl_y", O_RDWR);
		if(fd  == -1)
  		{  
    			printf("Please give the necessary permissions for device file in /dev/adxl_y\n");
    			exit(-1);
  		}
  
  		read(fd,&value,2);
  		printf("Accelerometer y_axis value is %d\n",value);
		printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		break;
	

case 'z': 
		fd=open("/dev/adxl_z", O_RDWR);
		if(fd  == -1)
  		{  
    			printf("Please give the necessary permissions for device file in /dev/adxl_z\n");
    			exit(-1);
  		}
  
  		read(fd,&value,2);
  		printf("Accelerometer z_axis value is %d\n",value);
		printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		break;

case 'e': printf("Exiting\n");
	  break;


default:{ printf("Please press a valid key\n");
	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	}
	}


  }while(s!='e');
  
  close(fd);
  return 0;
}
