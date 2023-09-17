/*
   Desarrollado por Creatvra S.A.S. - Ing Duvan Camilo Puerto - Bogota - Colombia
   
   Tercer Proyecto Librería "TODO" 
   Sketch para controlar las octavas del piano

    Arduino subirá a cada nota una octava hasta
    llegar al punto en que no es audible entonces
    volverá a la octava más baja posible


    Se necesita un Pulsador el cual
    ira de la siguiente manera:

            _[]_
    pin -----  ----|
                   |
                   |
                   Gnd

    Los interruptores o pulsadores como tambien se les
    conoce, necesitan una resistencia para que funcionen
    correctamente, esta se utiliza para impedir que el 
    sistema tenga errores.Con el fin de evitar usar mas 
    componentes electrónicos se usará la resistencia 
    interna de los pines digitales llamada:
    
    "Resistencia de Pull UP"

    Esta se activa con la funcion ActivarResistencia.


 Para mayor información dirigirse a la pagina "XXXXXXXXXX"

*/




#include <TODO.h>

TODO H;   // Se crea un objeto llamado H para usar el piano


int Parlante1 = 10;
int Parlante2 = 11;
int PinEnvio  = 12;
int Cali = 55;  // Se aconseja dejar este valor a menos que el sistema falle, Mirar ejemplo Calibración


int Octavas;


int Sw1 = 14;   // Pulsador en el pin 14 digital o en el Pin 0 analogo (Son lo mismo)


void setup() {  
  
  H.ActivarResistencia(Sw1);  // Activamos la resistencia interna de arduino para no usar una externa

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


  H.ModoPiano(Activar_Piano, Apagar_Sinte, Apagar_Midi);   // Esta funcion es la mas importante, Controla el sistema completo

}

void loop() {


  Octavas  = digitalRead(Sw1);    // Leemos el puerto digital

  if(Octavas == 0) {H.Octavas();}   // Si se oprime el interruptor entonces, Se cambia a la siguiente octava

     
    // La rutina para el piano es sencilla, si se oprime alguna de las teclas del piano
    // entonces sonará la nota pero si no se oprime se debe apagar todo
  if( H.Nota1() | H.Nota2() | H.Nota3() | H.Nota4() | H.Nota5() | H.Nota6() | H.Nota7() | H.Nota8() )
  {

   H.playPiano();

  }   

  else{H.noTono();}

}




