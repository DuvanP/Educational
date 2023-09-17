#include <Servo.h>

#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>


int  RECV_PIN = 7;
int  PRO[6];

IRrecv irrecv(RECV_PIN);

decode_results results;


Servo miServo;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  miServo.attach(4);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value

    
  }
  delay(100);

  if(results.value == 0xFD00FF) {
    
    digitalWrite(5,HIGH);     
    miServo.write(300); 

    Serial.begin(9600);
    Serial.print('F',DEC);

    Serial.end();
    delay(100);

    // la idea es crear un arreglo que me permita c}guardar la direccion que me envia el sensor infrarrojo
    // al tener guardada esa informacion ahora si se puede pasar por el if de esta manera tener el control de el
    // boton del teclado. El problema radica en la repeticion continua de la recepcion del dato.
    // por alguna razon no borra el registro y el dato sigue permaneciendo alli hasta que recive otro dato
  }

    
  if(results.value == 0xFD00FF) { digitalWrite(5,LOW);}

  if(results.value == 0xFD807F) { digitalWrite(6,HIGH);     miServo.write(150);}
    delay(100);
  if(results.value == 0xFD807F) { digitalWrite(6,LOW);}

    if(results.value == 0xFD40BF) { digitalWrite(7,HIGH);     miServo.write(90);}
    delay(100);
  if(results.value == 0xFD40BF) { digitalWrite(7,LOW);}


}

