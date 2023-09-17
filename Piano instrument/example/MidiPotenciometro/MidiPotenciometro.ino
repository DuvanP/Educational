/*
   Desarrollado por Creatvra S.A.S. - Ing Duvan Camilo Puerto - Bogota - Colombia
   
   Decimo Proyecto Librería "TODO" 
   
    Sketch para crear un control midi, en esta
    ocasión se trata de un potenciómetro para
    controlar el volumen o la intensidad de 
    cualquier valor que deseemos.

      1. Conectar el arduino al computador
      2. Subir este sketck al arduino.
      3. Desconectar el arduino del computador
      4. Mover el seleccionador llamado Midi On
         que esta en la shield Midi que viene con
         el kit de música.
      5. Conectar el Arduino al computador de nuevo
         ahora, el computador reconocerá el arduino
         como un dispositivo midi y no como un 
         arduino natural, por esta razón para poder 
         cargar otro nuevo código al arduino necesitaras
         cambiar el seleccionar a modo Arduino On que se
         encuentra en la shield.
      6. Abrir un programa DAW como LMMS aunque también
         funcionan en otros como por ejemplo Ableton, 
         GarageBand, Ardour, etc.
      7. Configura algún instrumento midi en el software
         como MOCO LUFA el cual es el nombre midi de arduino

      Nota: DAW = Digital Audio Workstation
                = Estación de trabajo de audio digital

    Conecta un potenciómetro en alguno de los canales
    análogos, como se ve en el siguiente circuito:

                    _____
    GND -------  --/     \
    Pin -------  --  (O)  |   Potenciómetro
    5v  -------  --\_____/


    Esta libreria solo permite el uso de 6 potenciometros.


     Para mayor información dirigirse a la página "XXXXXXXXXX"


*/
#include <TODO.h>

TODO H;   // Se crea un objeto llamado H para usar la libreria

int Po1 = 17;   // Potenciómetro conectado al pin 17 o al pin 3 analogo ( Son lo mismo)


void setup() {  
  
  Serial.begin(31250);  // Se ajusta la velocidad de comunicación MIDI:
  
  H.ModoPiano(Apagar_Piano, Apagar_Sinte, Activar_Midi);   // Esta función es la más importante, 
                                                            // Controla el sistema completo

}

void loop() {


  int VaPo1 = analogRead(Po1);    // Leemos el valor del potenciómetro

  H.Potenciometro1(1,16,VaPo1);   /* Esta función es la encargada de comunicarse con el
                                   programa DAW. Es importante entender la estructura:
                                   

                                   Potenciometro1( Canal Midi, Controlador, Intensidad) ;

                                   En este caso, vamos a usar el canal 1, el controlador 16
                                   y la intensidad que el potenciómetro nos indique en la
                                   variable Vapo1.

                                   De esta misma forma debemos configurarlo en LMMS

                                  */
}




