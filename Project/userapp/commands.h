
#ifndef _COMMANDS_H
#define _COMMANDS_H

#define EP_OUT 0x00

#define MAGIC_NUMBER 'T'
#define ADC_SEQ 0x01



#define THRESHOLD _IOW(MAGIC_NUMBER,ADC_SEQ,unsigned long)



#endif
