
#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "mys.h"
#include "hd44780.h"
#define LCD_BITS 4
#define RW_LINE_IMPLEMENTED 0 

int speed, dose_go,dose_set=0x04; 
int pos1, pos2, pos3, pos4; //�������, ����������� ��������� ��
int temp1, temp2, c, i, j, k,sum;
int butm = 1;
int dosa = 1;// dose
int speedv = 1;//speed
int mas[5];

void mfin(void){
   sum=0;
   for (j = 0; j < 15; j++) { 
       sum += masfile[j];
       }}

void pos(){  
    pos1 = 0b00001001;
    pos2 = 0b00000011;
    pos3 = 0b00000110;
    pos4 = 0b00001100;}

void word(void){
    lcd_puts ("dose =");
    lcd_goto (0x40);
    lcd_puts("speed ="); 
    }
void strelka(c){ 
   lcd_goto(0x49);
   if (c==1){ lcd_puts("--");lcd_putc('>');}

if (c==0){//left
	    lcd_putc('<');lcd_puts("--");}}
   
void numbersa(dosa){
     if (dosa == 1){lcd_putc('1');}
     if (dosa == 2){lcd_putc('2');}
     if (dosa == 3){lcd_putc('3');}
     if (dosa == 4){lcd_putc('4');}
     if (dosa == 5){lcd_putc('5');}
	} 
void numberss(speedv){//notm
     if (speedv == 1){lcd_putc('1');}
     if (speedv == 2){lcd_putc('2');}
     if (speedv == 3){lcd_putc('3');}
     if (speedv == 4){lcd_putc('4');}
     if (speedv == 5){lcd_putc('5');}
  }
  
void no_button(){}
void delay_for_start_and_set_buttons(void)
{
   TCCR0 = 0b00000000; //��������� ���������� �� ������� ������
   _delay_ms(140);  
   TCCR0 = 0b00000010; //��������� ���������� �� �������
   }	   
	      
void inc_speed(speed)
 {
    temp2 = speed +15;
    OCR1AH = temp2; //��������� ������� ��������  ��
    OCR1AL = 0x00; //��������� ������ �������� ��
    }    
    	   
void start(dose_set)
   {
      TCCR1B = 0b00001010; //��������� ���������� �� ������� ��
      PORTA |= (1 << 0);
      if (i<5){i++;}
      mas[i]=dose_set;
      delay_for_start_and_set_buttons();
      }
void inc_dose_lcd(dosa){
   lcd_goto(0x06);
		 numbersa(dosa);
		 }
		 
void inc_speed_lcd(speedv){
   lcd_goto(0x47);
		     numberss(speedv);
		     }

void increment(dosa, speedv,c){
	if (PINA&0b00000011){inc_dose_lcd(dosa);}
        if (PINA&0b00000101){inc_speed_lcd(speedv);}
        if (PINA&0b00001001) {strelka(c);}}
		 
void dec_speed(speed)
{
   temp2 = speed - 15; 
   OCR1AH = temp2; 
   OCR1AL = 0x00;         
   }   

void dec_dose_lcd(dosa){
   lcd_goto(0x06);
	      numbersa(dosa); }
		 
void dec_speed_lcd(speedv){
   lcd_goto(0x47);
	      numberss(speedv);
	      }
   
void decrement(dosa, speedv, c)
	{
	   if (PINA&0b00000011) {dec_dose_lcd(dosa); }
	   if (PINA&0b00000101) {dec_speed_lcd(speedv);}
	  if (PINA&0b00001001) { strelka(c); }
	   }
  

void rotate_forward(void)
{
   pos();
   temp1 = PORTC;// ���������  ��
   if (temp1 == pos1){PORTC = pos4;} 
   if (temp1 == pos4){PORTC = pos3; }
   if (temp1 == pos3){PORTC = pos2;}
   if (temp1 == pos2){PORTC = pos1; }
   }   

void rotate_backward(void)
{
   pos();
    temp1 = PORTC; //��������� ��
   if (temp1 == pos1){PORTC = pos2;} 
   if (temp1 == pos4){PORTC = pos1; }
   if (temp1 == pos3){PORTC = pos4;}
   if (temp1 == pos2){PORTC = pos3; }
   }  
  
 void stop_rotate(void)
{
   TCCR1B = 0b00000000; //��������� ���������� �� ������� ��
   PORTA = 0x00; 
   }   

void signmas(){
   mfin();
   dose_set=0;
   k=-1;i=-1;
   while(k<j){k++;
   dose_set=masfile[k];
   start();}}
   
void button2(){
     if (PINA&0b00000010){
		if (dosa >= 5){no_button();}
		if (dosa< 5){ dosa ++;}
		_delay_ms(140);   
		temp2 =  dose_set + 0x04;
	        dose_set =temp2;
		}
     if (PINA&0b00000100){
		      if (speedv >= 5){no_button();}
		      if (speedv < 5){speedv++;}
		     _delay_ms(140); inc_speed(speed);
		     }
    if (PINA&0b00001000){c=1;}}  
		   
void button3(){
   if (PINA&0b00000010) {
		if (dosa > 1){dosa--;}
		if (dosa <= 1){no_button();}
	_delay_ms(140);	//dec_dose(dose_set);
		 temp2 = dose_set - 0x04;    ///��������� ����
      dose_set = temp2; }
   if (PINA&0b00000100) {
		if (speedv > 1){speedv--;} 
		if (speedv <= 1){no_button();}
		_delay_ms(140);dec_speed(speed);}
   if (PINA&0b00001000){c=0;}}

void buttonoff(){
	     if (PINA&0b00000001){PORTA =0b00000001;} 
	     else {PORTA=0x00;}//4button
		  if (1<= butm <5) {butm ++;}
		  if (butm == 5){butm = 1;}
		  _delay_ms(140);}   
	
void button1(){
	    _delay_ms(140);
	    if (PINA&0b00010000){dose_go=sum;signmas();}
	    if(!(PINA&0b00010000)){
	    dose_go=dose_set;
	    start();}	}	  
		  
		  
ISR(TIMER1_COMPA_vect)
   {
      dose_go--; // �������� ������� ��
     temp1=dose_go; 
      if (temp1 == 0){stop_rotate();}
      if (c ==  1) {rotate_backward();}
      if (c == 0) {rotate_forward();}
      }
    
ISR(TIMER0_COMP_vect)  //��������� ������ � ������
      {
	if (!(PINB&0b00001010))//2button
	    {button2();}
	if (!(PINB&0b00001000)){;
	       increment(dosa, speedv,c); 
	   decrement(dosa, speedv,c);}

	  if (!(PINB&0b00001100)){//3button
	     button3();}
	      
	  if (PINB&0b00001000) {buttonoff();}     
	 if (!(PINB&0b00001000))
	    {
	        PORTA |=(1<< butm);
	       } 
         if (!(PINB&0b00001001)){button1();}
	    }
	 
      
int main(void)
 { 
    lcd_init (); //������������� �������
    lcd_clrscr (); //������� �������
    word();
    mfin();

    DDRC =0b00001111; //���� � �� - �� output 
    PORTC = 0b00000011; //�������� �������� � ����a �� 
    DDRA = 0b00011111; //����������- �� output 
    PORTA = 0b00000000; //���������� 0000
    DDRB = 0; // ������ - �� input
     PORTB = 0b00001111;  
    
    speed=171; 
    OCR1AH = speed; //��������� ������� �������� ��
    OCR1AL = 0x00;   // ������ ���������� 0
    
    TCNT1H = 0x00; //o������� ������� ���� ������� 1
    TCNT1L = 0x00; //o������� ������ ���� ������� 1
    TCCR1A = 0; //����� ������ ������� �� ���������

    TCCR0 = 0b00001010 ; //�������� ����� ������� ������������ ������ 
    OCR0 = 250;  //3������� ��� ������ ���������� ������� ������ �� ���������
    TCNT0 = 0x00; // �������� ������
    TIMSK = 0b01000001;  // ��������� ���������� �������� 0 � 1    
    PORTA=0b00000010;//������ ��������� ������ ��������� ���� 
    TCCR1B = 0; //��������� ���������� �� ������� ��� �� �� ������� ������ "����"
    pos(); 
    sei();

    while (1); 
 }
 