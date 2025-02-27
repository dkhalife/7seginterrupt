#line 1 "C:/Users/Dan/Desktop/Multiplexed 7Seg with Interrup/multii7.c"
#line 17 "C:/Users/Dan/Desktop/Multiplexed 7Seg with Interrup/multii7.c"
const unsigned int _pA=0b00000001;
const unsigned int _pB=0b00000010;
const unsigned int _pC=0b00000100;
const unsigned int _pD=0b00001000;
const unsigned int _pE=0b00010000;
const unsigned int _pF=0b00100000;
const unsigned int _pG=0b01000000;
const unsigned int _pH=0b10000000;

unsigned long int Cnt=0;
unsigned char Flag=1;
unsigned char D1,D2,D3,D4=0;




unsigned char Display(unsigned char no){
 unsigned char Pattern;
 unsigned char SEGMENT[]={
 0xFF&(~_pG)&(~_pH),
 _pB|_pC,
 0xFF&(~_pC)&(~_pF)&(~_pH),
 0xFF&(~_pE)&(~_pF)&(~_pH),
 _pB|_pC|_pF|_pG,
 0xFF&(~_pB)&(~_pE)&(~_pH),
 0xFF&(~_pB)&(~_pH),
 _pA|_pB|_pC,
 0xFF&(~_pH),
 0xFF&(~_pE)&(~_pH),
 };
 Pattern=SEGMENT[no];
 return(Pattern);
}





void interrupt(){
 TMR0L=100;
#line 70 "C:/Users/Dan/Desktop/Multiplexed 7Seg with Interrup/multii7.c"
 INTCON=0x20;
 Flag++;
 if(Flag>4){
 Flag=1;
 }
  PORTB.F0 = PORTB.F1 = PORTB.F2 = PORTB.F3 =0;
 D4=Cnt/1000;
 D3=(Cnt-D4*1000)/100;
 D2=(Cnt-D4*1000-D3*100)/10;
 D1=(Cnt-D4*1000-D3*100-D2*10);
 switch(Flag){
 case 1:
 PORTC=Display(D1);
  PORTB.F0 =1;
 break;

 case 2:
 PORTC=Display(D2);
 if(Cnt>=10){
  PORTB.F1 =1;
 }
 break;

 case 3:
 PORTC=Display(D3);
 if(Cnt>=100){
  PORTB.F2 =1;
 }
 break;

 case 4:
 PORTC=Display(D4);
 if(Cnt>=1000){
  PORTB.F3 =1;
 }
 break;
 }
}

void main() {










 OSCCON=0x6E;

 TRISC=0x00;
 TRISB=0x00;

  PORTB.F0 =0;
  PORTB.F1 =0;
  PORTB.F2 =0;
#line 142 "C:/Users/Dan/Desktop/Multiplexed 7Seg with Interrup/multii7.c"
 T0CON=0xC4;
 TMR0L=100;
#line 157 "C:/Users/Dan/Desktop/Multiplexed 7Seg with Interrup/multii7.c"
 INTCON=0xA0;
 Delay_ms(1000);

 for(;;){
 Cnt++;
 if(Cnt-10000==0){
 Cnt=0;
 }
 Delay_ms(125);
 }
}
