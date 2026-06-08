#include<LPC21xx.h>
#define lcd_d 0xf<<14
#include "4blcd.c"
#define rs 1<<12
#define e 1<<13
#define LED 1<<7
#define FAN 1<<8

void UART0_CONFIG(void)
 {
 PINSEL0=0x00000005;
 U0LCR=0X83;
 U0DLL=97;
 U0LCR=0x03;
 }
void UART0_TX(unsigned char d)
 {
 while((U0LSR&(1<<5))==0);
 U0THR=d;
 }
unsigned char UART0_RX(void)
{
while((U0LSR&(1<<0))==0);
return U0RBR;
}

int main()
{
unsigned char data;
lcd_init();
lcd_string("HOME AUROMATION");
IODIR0|=LED|FAN;
IOSET0=LED;
IOCLR0=FAN;
UART0_CONFIG();
while(1)
{
data=UART0_RX();
if(data=='L')
{
IOCLR0=LED;
lcd_cmd(0xc0);
lcd_string("LED ON");
}
else if(data=='F')
{
IOSET0=FAN;
lcd_cmd(0xc0);
lcd_string("FAN ON");
}
else if(data=='T')
{
IOSET0=LED;
lcd_cmd(0xc0);
lcd_string("FAN AND LED ON");
}
else if(data=='O')
{
IOCLR0=FAN;
lcd_cmd(0xc0);
lcd_string("ALL OFF");
}
}
 }