float Leer_Sensor_Presion(int media){
   float promediopresion=0.0;
   float VG=0.0,VS=0.0,G2=0.0;
   
   Filtro_Downflow_adc=sensores(PresDownFlow);
   V1=Filtro_Downflow_adc; 
   
   //-----------MPXV5004DP------------------// 
   
   Presion=(V1/G)-1.0;// Presion=(Voltaje/Ganancia)-1
   
   //-----------MPXV7002DP------------------// 
   //VS = (V1*5.0)/1023.0;   //Lectura de Divisor de Voltaje de PT100 con resistencia de 1k (+-10%)
   //G2=G;
   //VG = (G2*5.0)/1023.0;
   //Presion=(VS-VG);// Presion=(Voltaje/Ganancia)-1
   //Presion=(V1/G)-1.0;// Presion=(Voltaje/Ganancia)-1
   
   if(Presion<0.0)
   {
      Presion=0.0;
   }

   if(r>media-1)
   {r=0;}
   PromPresion[r]=Presion*4.02;r++;
         
   for(q=0;q<=(media-1);q++)
   {
      promediopresion+=PromPresion[q];
   } 
   promediopresion=promediopresion/media;   
   
   return promediopresion*Ajuste2;
}

float leeTemperatura(int8 media){
   float ADC=0,V=0,T=0,Tempera=0;
   ADC=sensores(0);
   V=5*ADC/1023;
   T=V/0.01;
   if(l2>media)
      l2=0;
      
   promedio2[l2]=T;l2++;
   Tempera=0;
     
     for(h2=0;h2<=(media-1);h2++){
        Tempera+=promedio2[h2];
     }      
   return Tempera/media;
}

void LeeEEPROM(void){
   Password[0]=read_eeprom(0);
   delay_ms(10);
   Password[1]=read_eeprom(1);
   delay_ms(10);
   Password[2]=read_eeprom(2);
   delay_ms(10);
   Password[3]=read_eeprom(3);
   delay_ms(10);
   Tpurgap[0]=read_eeprom(4);
   delay_ms(10);
   Tpurgap[1]=read_eeprom(5);
   delay_ms(10);
   Tpurgap[2]=read_eeprom(6);
   delay_ms(10);
   Tpurgap[3]=read_eeprom(7);
   delay_ms(10);
   Tppurgap[0]=read_eeprom(8);
   delay_ms(10);
   Tppurgap[1]=read_eeprom(9);
   delay_ms(10);
   Tppurgap[2]=read_eeprom(10);
   delay_ms(10);
   Tppurgap[3]=read_eeprom(11);
   delay_ms(10);
   Tuv[0]=read_eeprom(12);
   delay_ms(10);
   Tuv[1]=read_eeprom(13);
   delay_ms(10);
   Tuv[2]=read_eeprom(14);
   delay_ms(10);
   Tuv[3]=read_eeprom(15);
   delay_ms(10);
   Ttrabajo[0]=read_eeprom(16);
   delay_ms(10);
   Ttrabajo[1]=read_eeprom(17);
   delay_ms(10);
   Ttrabajo[2]=read_eeprom(18);
   delay_ms(10);
   Ttrabajo[3]=read_eeprom(19);
   delay_ms(10);
   //flag_alarma=read_eeprom(20);
   //delay_ms(10);
   Tempouvp[0]=read_eeprom(21);
   delay_ms(10);
   Tempouvp[1]=read_eeprom(22);
   delay_ms(10);
   Tempouvp[2]=read_eeprom(23);
   delay_ms(10);
   Tempouvp[3]=read_eeprom(24);
   
   delay_ms(10);
   Entero=read_eeprom(25);//Decimal1=read_eeprom(26);
   delay_ms(10);
   Temporal=read_eeprom(26);
   delay_ms(10);
   Temporal=Temporal/10.0;
   Ajuste1=Entero+Temporal;
   
   
   Entero=read_eeprom(27);//Decimal1=read_eeprom(26);
   delay_ms(10);
   Temporal=read_eeprom(28);
   delay_ms(10);
   Temporal=Temporal/10.0;
   Ajuste2=Entero+Temporal;
   
   zero_actual=make16(read_eeprom(30),read_eeprom(29));
   delay_ms(10);
   minutos_trabajo=make16(read_eeprom(34),read_eeprom(33));
   delay_ms(10);
   minutos_uv=read_eeprom(31);
   delay_ms(10);
   VelMotor=read_eeprom(32);
   delay_ms(10);
   
   Diferencia=make16(read_eeprom(61),read_eeprom(60));
   delay_ms(10);
   G=make16(read_eeprom(63),read_eeprom(62));
   delay_ms(10);
   negativo=read_eeprom(50);
   delay_ms(10);

}

void LimitaValores(void){
   if(Password[0]>9 || Password[0]<0){
      Password[0]=0;write_eeprom(0,0);
   }
   if(Password[1]>9 || Password[1]<0){
      Password[1]=0;write_eeprom(1,0);
   }
   if(Password[2]>9 || Password[2]<0){
      Password[2]=0;write_eeprom(2,0);
   }
   if(Password[3]>9 || Password[3]<0){
      Password[3]=0;write_eeprom(3,0);
   }
   if(Tpurgap[0]>9 || Tpurgap[0]<0){
      Tpurgap[0]=0;write_eeprom(4,0);
   }
   if(Tpurgap[1]>9 || Tpurgap[1]<0){
      Tpurgap[1]=0;write_eeprom(5,0);
   }
   if(Tpurgap[2]>9 || Tpurgap[2]<0){
      Tpurgap[2]=2;write_eeprom(6,2);
   }
   if(Tpurgap[3]>9 || Tpurgap[3]<0){
      Tpurgap[3]=0;write_eeprom(7,0);
   }
   if(Tppurgap[0]>9 || Tppurgap[0]<0){
      Tppurgap[0]=0;write_eeprom(8,0);
   }
   if(Tppurgap[1]>9 || Tppurgap[1]<0){
      Tppurgap[1]=0;write_eeprom(9,0);
   }
   if(Tppurgap[2]>9 || Tppurgap[2]<0){
      Tppurgap[2]=2;write_eeprom(10,2);
   }
   if(Tppurgap[3]>9 || Tppurgap[3]<0){
      Tppurgap[3]=0;write_eeprom(11,0);
   }
   if(Tuv[0]>9 || Tuv[0]<0){
      Tuv[0]=0;write_eeprom(12,0);
   }
   if(Tuv[1]>9 || Tuv[1]<0){
      Tuv[1]=0;write_eeprom(13,0);
   }
   if(Tuv[2]>9 || Tuv[2]<0){
      Tuv[2]=0;write_eeprom(14,0);
   }
   if(Tuv[3]>9 || Tuv[3]<0){
      Tuv[3]=0;write_eeprom(15,0);
   }
   if(Ttrabajo[0]>9 || Ttrabajo[0]<0){
      Ttrabajo[0]=0;write_eeprom(16,0);
   }
   if(Ttrabajo[1]>9 || Ttrabajo[1]<0){
      Ttrabajo[1]=0;write_eeprom(17,0);
   }
   if(Ttrabajo[2]>9 || Ttrabajo[2]<0){
      Ttrabajo[2]=0;write_eeprom(18,0);
   }
   if(Ttrabajo[3]>9 || Ttrabajo[3]<0){
      Ttrabajo[3]=0;write_eeprom(19,0);
   }
   if(Tempouvp[0]>9 || Tempouvp[0]<0){
      Tempouvp[0]=0;write_eeprom(21,0);
   }
   if(Tempouvp[1]>9 || Tempouvp[1]<0){
      Tempouvp[1]=0;write_eeprom(22,0);
   }
   if(Tempouvp[2]>9 || Tempouvp[2]<0){
      Tempouvp[2]=0;write_eeprom(23,0);
   }
   if(Tempouvp[3]>9 || Tempouvp[3]<0){
      Tempouvp[3]=1;write_eeprom(24,1);
   }
   if(Ajuste1>2.0){
      Ajuste1=1.5;write_eeprom(25,1);write_eeprom(26,5);
   }
   if(Ajuste2>2.0){
      Ajuste2=1.0;write_eeprom(27,1);write_eeprom(28,0);
   }
   if(zero_actual>300){
      zero_actual=203;write_eeprom(29,203);write_eeprom(30,0);
   }
   if(minutos_uv>60){
      minutos_uv=0;write_eeprom(31,0);
   }
   if(VelMotor>6){
      VelMotor=2;write_eeprom(32,2);
   }   
   if(minutos_trabajo>3600){
      minutos_trabajo=0;write_eeprom(33,0);write_eeprom(34,0);
   }
   //if(Relacion>2.0){
      //Relacion=0.57;write_eeprom(35,0);write_eeprom(36,57);
   //}
   if(Diferencia>200){
      Diferencia=0;write_eeprom(60,0);write_eeprom(61,0);
   }
   if(G<180 || G>350){
      G=240;write_eeprom(62,240);write_eeprom(63,0);
   }
   if(negativo>20){
      negativo=10;write_eeprom(50,10);
   }
}

void VelocidadMotor(int8 Vel){
   if(Vel==6){
      Porcentaje=0;
      Motor_on;
   }else if(Vel==5){
      Porcentaje=15;
      retardo=2000;
   }else if(Vel==4){
      Porcentaje=25;
      retardo=3000;
   }else if(Vel==3){
      Porcentaje=35;
      retardo=3600;
   }else if(Vel==2){
      Porcentaje=45;
      retardo=4300;
   }else if(Vel==1){
      Porcentaje=50;
      retardo=5000;
   }else if(Vel==0){
      Porcentaje=100;
      Motor_off;
   }
}

short PidePassword(int8 MenuAnt, int8 MenuActual, int8 MenuPost, int8 clave0,int8 clave1, int8 clave2,int8 clave3){
      if(n==0)
      {
         displayContrasena(Contrasena[0],20,30,1);displayContrasena(Contrasena[1],40,30,0);
         displayContrasena(Contrasena[2],60,30,0);displayContrasena(Contrasena[0],80,30,0);
         strcpy(Menus.Letra,"Clave");
         displayMenu(Menus.Letra,20,0,1,3);
         n=1;
      }
      
      if(UP){
         flag_latencia=0;t_latencia=0;
         if(Flanco == 0){
            Flanco = 1;delay_ms(5);
            for(i=1;i<=4;i++){
               if(unidad==i){
                  Contrasena[i-1]++;
                  if(Contrasena[i-1]>9){
                     Contrasena[i-1]=0;
                  }
                  displayContrasena(Contrasena[i-1],i*20,30,1);
               }else{
                  displayContrasena(Contrasena[i-1],i*20,30,0);
               }
            }
         }
      }else{
         Flanco = 0;
      }
            
      if(DOWN){
         flag_latencia=0;t_latencia=0;
         if(Flanco2 == 0){
            Flanco2 = 1;delay_ms(5);
            for(i=1;i<=4;i++){
               if(unidad==i){
                  Contrasena[i-1]--;
                  if(Contrasena[i-1]<0){
                     Contrasena[i-1]=9;
                  }
                  displayContrasena(Contrasena[i-1],i*20,30,1);
               }else{
                  displayContrasena(Contrasena[i-1],i*20,30,0);
               }
            }      
         }     
      }else{
         Flanco2 = 0;
      }
            
      if(RIGHT){
         flag_latencia=0;t_latencia=0;
         if(Flanco1 == 0){
            Flanco1 = 1;delay_ms(5);unidad++;
            for(i=1;i<=4;i++){
               if(unidad==i){
                  displayContrasena(Contrasena[i-1],i*20,30,1);
               }else{
                  displayContrasena(Contrasena[i-1],i*20,30,0);
               }
            }
         }
      }else{
         Flanco1 = 0;
      }
      
      if(LEFT){
         delay_ms(100);
         if(LEFT){
            Menu=MenuAnt;glcd_fillScreen(OFF);n=0;Opcion=1;unidad=1;
            Contrasena[0]=0;Contrasena[1]=0;Contrasena[2]=0;Contrasena[3]=0;
            glcd_fillScreen(OFF);glcd_update();
            return 1;
         }
      }
    
      if(unidad>4){
         glcd_fillScreen(OFF);unidad=1;flag_latencia=0;t_latencia=0;
         
         if(Contrasena[0]==3&&Contrasena[1]==8&&Contrasena[2]==9&&Contrasena[3]==2 && MenuActual==0){ // Si Ingresa clave para reset general del sistema.
            write_eeprom(0,0);delay_ms(20);write_eeprom(1,0);delay_ms(20);// Reestablece a contrase�a de Fabrica y reinicia Programa.
            write_eeprom(2,0);delay_ms(20);write_eeprom(3,0);delay_ms(20);
            reset_cpu();
         }
      
         if((Contrasena[0]==clave0)&&(Contrasena[1]==clave1)&&(Contrasena[2]==clave2)&&(Contrasena[3]==clave3)){
            glcd_fillScreen(OFF);
            strcpy(Menus.Letra,"Clave");
            displayMenu(Menus.Letra,30,0,0,2);
            strcpy(Menus.Letra,"Correcta");
            displayMenu(Menus.Letra,15,30,0,2);
            Menu=MenuPost;glcd_update();delay_ms(1000);glcd_fillScreen(OFF);
            Contrasena[0]=0;Contrasena[1]=0;Contrasena[2]=0;Contrasena[3]=0;
            if(MenuActual==0)tiempo_purga=1;n=0;
            return 1;
         }else{
            glcd_fillScreen(OFF);
            strcpy(Menus.Letra,"Clave");
            displayMenu(Menus.Letra,30,0,0,2);
            strcpy(Menus.Letra,"Incorrecta");
            displayMenu(Menus.Letra,0,30,0,2);
            unidad=1;glcd_update();delay_ms(1000);Contrasena[0]=0;Contrasena[1]=0;Contrasena[2]=0;Contrasena[3]=0;glcd_fillScreen(OFF);
            glcd_rect(0, 0, 127, 25, YES, ON);strcpy(Menus.Letra,"Clave");glcd_text57(25, 1, Menus.Letra, 3, OFF);displayContrasena(Contrasena[0],20,30,1);
            displayContrasena(Contrasena[1],40,30,0);displayContrasena(Contrasena[2],60,30,0);displayContrasena(Contrasena[0],80,30,0);
            Menu=MenuAnt;glcd_fillScreen(OFF);n=0;
            return 0;
         }
      }
}
