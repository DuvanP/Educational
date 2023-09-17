/*
   Desarrollado por Creatvra S.A.S. - Ing Duvan Camilo Puerto - Bogota - Colombia
   
   Sexto Proyecto Librería "TODO" 
    Sketch para controlar el Vibrato del piano
    por medio de un potenciometro.


    Para controlar el tiempo del Vibrato se puede usar
    Un potenciometro conectado a alguno de los canales
    analogos, como se ve en el siguiente circuito:

                    _____
    GND -------  --/     \
    Pin -------  --  (O)  |   Potenciometro
    5v  -------  --\_____/

    Se necesita un interruptor el cual
    ira de la siguiente manera:

            _[]_
    pin -----  ----|
                   |
                   |
                   Gnd

    Los interruptores y los  pulsadores necesitan una
	resistencia para que funcionen correctamente, esta 
	se utiliza para impedir que el sistema tenga errores. 
	Con el fin de evitar usar mas componentes electrónicos
	se usará la resistencia interna de los pines digitales 
	llamada:
    
    "Resistencia de Pull UP"

    Esta se activa con la función ActivarResistencia.

 Para mayor información dirigirse a la página "XXXXXXXXXX"
*/

#include <TODO.h>

TODO H;   // Se crea un objeto llamado H para usar el piano


int Parlante1 = 10;
int Parlante2 = 11;
int PinEnvio  = 12;
int Cali = 55;  // Se aconseja dejar este valor a menos que el sistema falle, Mirar ejemplo Calibración


int Vibrato;
int Nivel;


int Sw1 = 14;   // Pulsador en el pin 14 digital o en el Pin 0 analogo (Son lo mismo)
int Pot1 = 15;  // Potenciometro en el pin 1 analogo o el pin 15 usado como analogo.


void setup() {  
  
  
  H.ActivarResistencia(Sw1);  // Activamos la resistencia interna en el pin 14 de arduino

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


  H.ModoPiano(Activar_Piano, Activar_Sinte, Apagar_Midi);   // Esta función es la más importante, 
                                                            // Controla el sistema completo

  H.Syntetizador(Activar_Sustain , Activar_Vibrato , Apagar_Delay);  // Esta función controla al sintetizador
                                                                      
}

void loop() {


  Vibrato  = digitalRead(Sw1);    // Leemos el puerto digital
  

  if(Vibrato == 0) {H.Vibrato(true);}   // Si se oprime el interruptor entonces Vibraran las notas
  else             {H.Vibrato(false);}  // Si se suelta el interruptor No funcionará el Vibrato

  Nivel = analogRead(Pot1);   // Leemos el potenciometro desde el pin analogo  
  H.TiempoVibrato(Nivel);    // Esta funcion permite controlar el efecto del Vibrato
     

    // La rutina para el piano es sencilla, si se oprime alguna de las teclas del piano
    // entonces sonará la nota pero si no se oprime se debe apagar todo
  if( H.Nota1() | H.Nota2() | H.Nota3() | H.Nota4() | H.Nota5() | H.Nota6() | H.Nota7() | H.Nota8() )
  {

   H.playPiano();

  }   

  else{H.noTono();}

}




