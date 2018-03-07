#include <16F1827.h>
#device *=16
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES INTRC_IO                 //Internal RC Osc, no CLKOUT
#FUSES WDT_SW                    //No Watch Dog Timer, enabled in Software
#FUSES PUT                       // Power Up Timer
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#use delay(int=4000000)
#use rs232(baud=9600,parity=N,xmit=PIN_A2,rcv=PIN_A1,bits=8,stream=ZIGBEE)
#use rs232(baud=9600,parity=N,xmit=PIN_A6,rcv=PIN_A4,bits=8,stream=USB)


char timed_getc_TinyBee() 
{   
   char donnee_zb;
   
   while(!kbhit())                  //tant qu'il n'y a rien sur la liaison serie ne rien faire.
      delay_us(10);
      
       if(kbhit())                  // si il y a quelque chose sur la liaison série
           donnee_zb = getc(ZIGBEE);// alors l'écrire dans la variable "donnee_zb"
        else                        // si non
           donnee_zb = 0;           // écrire "0" dans la variable "donnee_zb"
   return(donnee_zb);               // retourner "donnee_zb"
}


void main()
{
   //int1 status;
   char valeur_zigbee;
   short etat_bp=0;
 while(TRUE)
 {
   
   if (input(pin_b3)==0&&etat_bp==0)         // si appui sur le bp et que "etat_bp=0", alors
      {
         etat_bp=1;                          //etat_bp=1 et
         fprintf(ZIGBEE,"START\r");          // envoyer sur la liaison série zigbee "START"
         delay_ms(500);
      }
   else if(input(pin_b3)==1&&etat_bp==1)     // si relachement du bp et que etat bp = 1 alors,
      {
         etat_bp=0;                          // etat_bp=0
      }
      
      
   else //sinon
      {
          if(kbhit())  //Si reception d'un message sur la liaison série tinyBee, alors
          {
           valeur_zigbee=timed_getc_TinyBee(); //donnee_zb (retrounée précédement) = valeur_zigbee
           fputc(valeur_zigbee, USB);          //écrire valeur_zigbee sur la laison série USB
          }
      }
 }
}
