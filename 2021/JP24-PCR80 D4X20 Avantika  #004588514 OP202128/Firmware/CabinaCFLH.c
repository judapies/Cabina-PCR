// JP Inglobal.

#include <18F4550.h>
#device adc=10
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL1,CPUDIV4,VREGEN,NOMCLR,NOPUT
#use delay(clock=16000000)
#include <MATH.h>

// Definición de teclado - NC
#define   UP            !input(PIN_A5)
#define   DOWN          !input(PIN_E0)
#define   RIGHT         !input(PIN_E1)
#define   IZQU          !input(PIN_E2)
#define   VIDRIO        !input(PIN_A1)

// Definición de otros puertos
#define   Luz_UV_on         output_bit(PIN_B3,0)
#define   Luz_UV_off        output_bit(PIN_B3,1)
#define   Luz_Blanca_on     output_bit(PIN_B4,0)
#define   Luz_Blanca_off    output_bit(PIN_B4,1)
#define   Buzzer_on         output_bit(PIN_C0,1)
#define   Buzzer_off        output_bit(PIN_C0,0)
#define   ON  1
#define   OFF 0

short estadouv=0,estadofl=0,estadomv=0,Flanco=0,Flanco1=0,tiempo_cumplido=0,Lectura=0,flaguv=0,flagfl=0,estadobuzzer=0,infinito=0;
int8 Menu=1, Flecha=2,Flecha2=2, segundos=0,minutos=0,horasL=0,horasH=0;
int8 tempo_minutos=0,tempo_segundos=0,tempo_minutos_pro=0,tempo_segundos_pro=0,i=0,tiemporeset=0,guardaruv=0;
signed int8   paso=0;
int8 ActivaBuzzer=0;
int16 tiempos,horas=0;
short Cambio=ON;

#include <LCD420.c>
#include <Funciones.h>

#int_TIMER1
void temp1s(void){
   //set_timer1(45536);  // 5 ms
   set_timer1(45580);  // 5 ms
   tiempos++;
   if(tiempos>=200){   // Ha transcurrido una decima de segundo (PIC18F4550 con XT = 16MHZ)
   tiempos=0;tiemporeset++;Lectura=1;
   
      if(ActivaBuzzer==1){
         if(estadobuzzer==0){
            Buzzer_off;
         }else{
               Buzzer_on;
         }
         estadobuzzer=!estadobuzzer;
      }
   //----------------------------- Tiempo Total-----------------------------//
      if(estadouv==1 && infinito==0){
         segundos++;
         if(tiempo_cumplido==0){
            if(tempo_segundos>0){
               tempo_segundos--;
            }else{
               if(tempo_minutos>0){
                  tempo_minutos--;
                  tempo_segundos=59;
               }else{
                  tiempo_cumplido=1;
                  estadouv=0;
                  tempo_minutos=tempo_minutos_pro;tempo_segundos=tempo_segundos_pro;
               }
            }
         }
      }
   }
}

void main ()
{
   Luz_UV_off;
   Luz_Blanca_off;
   Buzzer_off;
   ConfigInterrupciones();
   MensajeBienvenida();
   LeeEEPROM(); 
   LimitaValores();
   output_bit(PIN_A0,0);output_bit(PIN_A2,0);output_bit(PIN_A3,0);
   output_bit(PIN_C1,0);output_bit(PIN_C2,0);output_bit(PIN_C6,0);output_bit(PIN_C7,0);
   output_bit(PIN_B0,0);output_bit(PIN_B5,0);output_bit(PIN_B6,0);output_bit(PIN_B7,0);
   Luz_UV_off;
   Luz_Blanca_off;
   Buzzer_off;
   if(UP && DOWN && RIGHT)
      resetFabrica();
   while(true){
         
//----------------Menu2---------------------------------------------------------------
   if(Menu == 2){ // Menu de tiempo de trabajo de Luz UV   
      lcd_gotoxy(1,1);
      printf(lcd_putc,"    Temporizador     ");
      lcd_gotoxy(1,2);
      printf(lcd_putc,"       Luz UV        ");
      lcd_gotoxy(6,3);
      printf(lcd_putc,"%03u Minutos  ",tempo_minutos_pro); 

   if(tempo_minutos_pro%5!=0){
      tempo_minutos_pro=5;
   }
   
   if(UP){
      delay_ms(20);
      if(UP){
         if(tempo_minutos_pro<240){
            tempo_minutos_pro+=5;delay_ms(300);
         }   
      }
   }
   
   if(DOWN){
      delay_ms(20);
      if(DOWN){         
         if(tempo_minutos_pro>0){
            tempo_minutos_pro-=5;delay_ms(300);
         } 
      }
   }
   
   if(IZQU || RIGHT){
      delay_ms(200);
      if(IZQU || RIGHT){
         printf(lcd_putc,"\f");
         lcd_gotoxy(1,2);
         printf(lcd_putc,"  Tiempo Almacenado");
         lcd_gotoxy(1,3);
         printf(lcd_putc,"    Correctamente  ");
         write_eeprom(0,tempo_minutos_pro);
         delay_ms(20);
         tempo_minutos=tempo_minutos_pro;tempo_segundos_pro=0;
         tempo_segundos=0;
         delay_ms(700);
         printf(lcd_putc,"\f");
         if(tempo_minutos_pro==0){
            infinito=1;
            lcd_gotoxy(1,2);
            printf(lcd_putc,"  Modo  Continuo ");
            lcd_gotoxy(1,3);
            printf(lcd_putc,"   Seleccionado  ");
         }else{
            infinito=0;
         }
         delay_ms(700);
         delay_ms(30);Menu=1; paso=0;Flecha=2;Flecha2=2;printf(lcd_putc,"\f");
      }
   }  
  }
//----------------Fin-Menu2---------------------------------------------------------------

//----------------Menu100---------------------------------------------------------------
   if(Menu == 1){ // Menu de seleccion de Estado de Luz UV   
   if(Lectura==1){
      Lectura=0;
      lcd_gotoxy(1,1);
      printf(lcd_putc,"JPCR ");      
      lcd_gotoxy(1,2);
      printf(lcd_putc,"Uso Luz UV: %05Lu H",horas);      
      if(horas>1500){
         lcd_gotoxy(6,1);
         printf(lcd_putc,"!Cambie Luz UV!");      
         ActivaBuzzer=1;
      }else{
         lcd_gotoxy(6,1);
         printf(lcd_putc,"               ");      
         ActivaBuzzer=0;
      }
      /*
      for(i=0;i<floor(Saturacion);i++){
         lcd_gotoxy(i+8,2);
         printf(lcd_putc,"Ñ");
      }
      
      for(i=floor(Saturacion);i<11;i++){
         lcd_gotoxy(i+8,2);
         printf(lcd_putc," ");
      }
      */
      
      lcd_gotoxy(1,3);
      printf(lcd_putc,"Temporizador:%03u:%02u",tempo_minutos,tempo_segundos);
   }
    
   if(tiempo_cumplido==1){ 
      printf(lcd_putc,"\f");
      lcd_gotoxy(1,2);
      printf(lcd_putc,"  Temporizador  de  ");
      lcd_gotoxy(1,3);
      printf(lcd_putc," Luz UV  Finalizado ");
      lcd_gotoxy(1,4);
      printf(lcd_putc,"                    ");
      lcd_gotoxy(1,1);
      printf(lcd_putc,"                    ");
      for(i=0;i<5;i++){
         Buzzer_on;
         delay_ms(200);
         Buzzer_off;
         delay_ms(200);
      }
      tiempo_cumplido=0;
      printf(lcd_putc,"\f");
   }
   
   //if(estadouv==1 && VIDRIO){
   if(estadouv==1){
      estadofl=0;
      Luz_Blanca_off;
      Luz_UV_on;
      if(flaguv==0){
         printf(lcd_putc,"\f");lcd_init();delay_ms(200);lcd_init();flaguv=1;guardaruv=1;Cambio=ON;
      }
   }else{
      estadouv=0;
      Luz_UV_off;
      if(flaguv==1){
         printf(lcd_putc,"\f");lcd_init();delay_ms(200);lcd_init();flaguv=0;guardaruv=1;Cambio=ON;
      }
   }
      
   if(estadofl==1){
      Luz_Blanca_on;
      if(flagfl==0){
         lcd_init();delay_ms(200);lcd_init();flagfl=1;Cambio=ON;
      }
   }else{
      Luz_Blanca_off;
      if(flagfl==1){
         lcd_init();delay_ms(200);lcd_init();flagfl=0;Cambio=ON;
      }
   }
   
   if(DOWN){//Si oprime hacia arriba   
      delay_ms(20);
      if(DOWN){
         if(Flanco == 0)
         {
            estadofl=!estadofl;Flanco = 1;delay_ms(300);Cambio=ON;
         }
      }
   }else{
      Flanco = 0;
   }
   
   if(RIGHT){//Si oprime hacia abajo
      delay_ms(20);
      if(RIGHT){
         if(Flanco1 == 0){
            estadomv=!estadomv;Flanco1 = 1;delay_ms(300);Cambio=ON;
         }
      }
   }else{
      Flanco1 = 0;
   }
   
   if(IZQU){//Si oprime hacia izquierda
      delay_ms(20);
      if(IZQU){
         delay_ms(150); 
         estadouv=!estadouv;
         Cambio=ON;
      }
   }
   
   if(estadouv==1){
      lcd_gotoxy(13,4);
      printf(lcd_putc," UV:ON ");
   }else{         
      lcd_gotoxy(13,4);
      printf(lcd_putc," UV:OFF");
   }
   
   if(estadofl==1){
      lcd_gotoxy(1,4);
      printf(lcd_putc,"Luz:ON ");
   }else{
      lcd_gotoxy(1,4);
      printf(lcd_putc,"Luz:OFF");
   }    
   
   if(guardaruv==1){
      write_eeprom(1,segundos);write_eeprom(2,minutos);
      horasL=make8(horas,0);
      horasH=make8(horas,1);
      write_eeprom(3,horasL);
      delay_ms(20);
      write_eeprom(4,horasH);
      delay_ms(20);
      guardaruv=0;
   }
   
   if(segundos>=60){
      segundos=0;minutos++;
   }
   if(minutos==60){
      minutos=0;horas++;
   }  
   
   if(UP){//Si oprime hacia izquierda
      delay_ms(20);
      if(UP){
         delay_ms(200);
         printf(lcd_putc,"\f");
         delay_ms(300);
         Menu=2; 
         paso=0;
         Flecha=2;
         Flecha2=2;
         Cambio=ON;
      }
   }
    
   }
//----------------Fin-Menu100--------------------------------------------------------------  
   if(tiemporeset>=60){
      lcd_init();delay_ms(200);lcd_init();
      tiemporeset=0;
   }
   
   }
}

