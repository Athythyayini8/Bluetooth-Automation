#include<LPC21xx.h>
#define rs 1<<12
#define e 1<<13

typedef unsigned int U32;
typedef unsigned char U8;
typedef signed char S8;
typedef float F32;

void delay_milliseconds(U32 milliseconds)

{
T0PR = 15000-1;
T0TCR = 0X01;
while(T0TC<milliseconds);
T0TCR = 0x03;
T0TCR = 0x00;
}

void lcd_cmd(U8 d)
{
    IOCLR0=lcd_d;
IOSET0 = (d&0xf0)<<10;
IOCLR0 = rs;
IOSET0 =e;
delay_milliseconds(2);                                    
IOCLR0 =e;

    IOCLR0=lcd_d;
IOSET0 = (d&0x0f)<<14;
IOCLR0 = rs;
IOSET0 =e;
delay_milliseconds(2);
IOCLR0 =e;
}


void lcd_data(U8 d)
{

IOCLR0=lcd_d;
IOSET0 = (d&0xf0)<<10;
IOSET0 = rs;
IOSET0 =e;
delay_milliseconds(2);
IOCLR0 =e;

    IOCLR0=lcd_d;
IOSET0 = (d&0x0f)<<14;
IOSET0 = rs;
IOSET0 =e;
delay_milliseconds(2);
IOCLR0 =e;
}
void lcd_init(void)
{
IODIR0 |= lcd_d|rs|e;
lcd_cmd(0x01);
lcd_cmd(0x02);
lcd_cmd(0x0c);
lcd_cmd(0x28);
lcd_cmd(0x80);

}
void lcd_string(U8 *s)
{
while(*s)
lcd_data(*s++);

}
