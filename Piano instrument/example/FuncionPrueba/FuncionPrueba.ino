/*
 *  Desarrollado por Creatvra S.A.S. - Ing Duvan Camilo Puerto - Bogota - Colombia
 *  
 *  Proyecto Prueba Librería "TODO" 
 *  
 *  Si quieres ver como funciona la libreria
 *  capacitiva sin necesidad de entrar en lo
 *  relacionado con el piano, entonces debes
 *  usar la funcion Prueba.
 *  
 *  Prueba nos ayuda a obtener los datos de la 
 *  tecla que se quiera.
 *  
 *  Esto nos ayuda a entender un poco como funciona
 *  toda la parte capacitiva.
 *  
 *  Para observar los numeros primero debes subir el código, luego
 *  abrir el monitor serial con el comando Contrl + TAB + m
 *
 *  
 *  Para mayor información dirigirse a la pagina "XXXXXXXXXX"
 *  
 */


#include <TODO.h>

TODO H;

int Parlante1 = 10;
int Parlante2 = 11;
int PinEnvio  = 12;
int Cali = 55;  // Se aconseja dejar este valor a menos que el sistema falle

int Pin_de_tecla = 2; // Escriba aqui el pin que se analizará

void setup() {
  
  Serial.begin(9600);
  
  H.Fiesta(Parlante1,Parlante2,PinEnvio);  // Calibra el pin de parlante1, parlante2, y senPin
  H.Calibracion(Cali);        // Calibracion de CALI y veces
  
  
}

void loop() {

    Serial.println(H.Prueba(Pin_de_tecla));      // Con la funcion Prueba puedes testear cualquier pin.

    delay(200);
    
  

}
