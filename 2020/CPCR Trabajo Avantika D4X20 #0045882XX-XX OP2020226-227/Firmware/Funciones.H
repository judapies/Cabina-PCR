void ConfigInterrupciones (void){
   lcd_init();
   set_tris_a(0XFF);
   set_tris_e(0XFF);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(global);
}

void MensajeBienvenida (void){
   lcd_gotoxy(1,1);
   printf(lcd_putc,"ESTACION DE  TRABAJO");
   lcd_gotoxy(1,2);
   printf(lcd_putc,"        PCR         ");
   lcd_gotoxy(1,3);
   printf(lcd_putc,"    JP  INGLOBAL    ");
   lcd_gotoxy(1,4);
   printf(lcd_putc,"    REF:JP24-PCR    ");
   delay_ms(2000);
   printf(lcd_putc,"\f");
}

void LeeEEPROM (void){
   // Lee la contraseña almacenada en la eeprom para poder comprobar con la que escribe el usuario.
   tempo_minutos=read_eeprom(0);
   delay_ms(20);
   segundos=read_eeprom(1);
   delay_ms(20);
   minutos=read_eeprom(2);
   delay_ms(20);
   horasL=read_eeprom(3);
   delay_ms(20);
   horasH=read_eeprom(4);
   delay_ms(20);
   horas=make16(horasH,horasL);
}

void LimitaValores(void){
   if(tempo_minutos>200){
      tempo_minutos=5;write_eeprom(0,5);delay_ms(20);
   }
   if(segundos>60){
      segundos=0;write_eeprom(1,0);delay_ms(20);
   }
   if(minutos>60){
      minutos=0;write_eeprom(2,0);delay_ms(20);
   }
   if(horas>10000){
      horas=0;write_eeprom(3,0);delay_ms(20);write_eeprom(4,0);delay_ms(20);
   }
   tempo_minutos_pro=tempo_minutos;tempo_segundos_pro=tempo_segundos;
   if(tempo_minutos_pro==0)
      infinito=1;
   else
      infinito=0;
}

void resetFabrica(){
   write_eeprom(0,0);
   delay_ms(20);
   write_eeprom(1,0);
   delay_ms(20);
   write_eeprom(2,0);
   delay_ms(20);
   /*
   //Prueba
   write_eeprom(3,0x89);
   delay_ms(20);
   write_eeprom(4,0x13);
   delay_ms(20);
   */
   write_eeprom(3,0);
   delay_ms(20);
   write_eeprom(4,0);
   delay_ms(20);
   
   lcd_gotoxy(1,4);
   printf(lcd_putc,"Reiniciando....");
   delay_ms(2000);
   MensajeBienvenida();
   LeeEEPROM();
   LimitaValores();
}
