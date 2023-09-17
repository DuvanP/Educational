/*
 *  Desarrollado por Creatvra S.A.S. - Ing Duvan Camilo Puerto - Bogota - Colombia
 *  
 *  Segundo Proyecto Librería "TODO" 
 *  
 *  
 *  En raras ocasiones, el piano puede que no funcione
 *  perfectamente debido a condiciones ambientales
 *  por esta razón es necesario calibrar el sistema
 *  para esto debes correr este sketch.
 *  
 *  Para calibrar el sistema debes subir el código, luego
 *  abrir el monitor serial con el comando Contrl + TAB + m
 *  
 *  El monitor serial te mostrará el valor de las 8 teclas,
 *  las cuales siempre deben estar en 0 a menos que tu 
 *  oprimas alguna de ellas.
 *  
 *  Si tu oprimes la tecla y esta no llega a 1 entonces
 *  súmale al valor de CALI un uno:
 *  
 *    CALI + 1
 *  Y realiza de nuevo la prueba hasta que funcione.
 *  
 * 
 *  Si alguna tecla de ellas siempre esta en 1 aunque tu
 *  no la toques (seguramente el piano también debe sonar
 *  infinitamente, entonces revisa las resistencias, pues
 *  es posible que no estén bien conectadas.
 *    
 *  
 *  
 *  Para mayor información dirigirse a la pagina "XXXXXXXXXX"
 *  
 */


 
#include <TODO.h>

TODO H;   // Se crea un objeto llamado H para usar el piano


int Cali = 55;  // Se aconseja dejar este valor a menos que el sistema falle

int Parlante1 = 10;
int Parlante2 = 11;
int PinEnvio  = 12;

void setup() {  
  
  Serial.begin(9600);  // Se ajusta la velocidad de comunicación con el monitor Serial
  
  
  H.Fiesta(Parlante1,Parlante2,PinEnvio);  // Calibra el pin de parlante1, parlante2, y senPin
  H.Calibracion(Cali);                     // Esta función calibra el sensor   

  H.Tecla1( 2,  Nota_Do_4   );               // Le asignamos el pin 2  de recepción y una frecuencia de Do4.  
  H.Tecla2( 3,  Nota_Re_4   );               // Le asignamos el pin 3  de recepción y una frecuencia de Re4.  
  H.Tecla3( 4,  Nota_Mi_4   );               // Le asignamos el pin 4  de recepción y una frecuencia de Mi4.  
  H.Tecla4( 5,  Nota_Fa_4   );               // Le asignamos el pin 5  de recepción y una frecuencia de Fa4.  
  H.Tecla5( 6,  Nota_Sol_4  );               // Le asignamos el pin 6  de recepción y una frecuencia de Sol4.  
  H.Tecla6( 7,  Nota_La_4   );               // Le asignamos el pin 7  de recepción y una frecuencia de La4.  
  H.Tecla7( 8,  Nota_Si_4   );               // Le asignamos el pin 8  de recepción y una frecuencia de Si4.  
  H.Tecla8( 9,  Nota_Do_5   );               // Le asignamos el pin 9  de recepción y una frecuencia de Do5.

  

}

void loop() {

H.DEBUGIN();    // Esta función es la que nos ayuda a detectar si esta bien calibrado el sistema.
                // Con la función DEBUGIN2(); puedes obtener el valor real de cada tecla.

}


