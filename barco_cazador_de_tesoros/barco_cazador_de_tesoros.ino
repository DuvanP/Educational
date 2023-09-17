#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>


#include <Servo.h>



const int RECV_PIN = 7;
const int vccIR = 6;
const int gndIR = 5;
const int servoPIN = 4;
const int motorPIN = 3;


Servo miServo;
IRrecv irrecv(RECV_PIN);
decode_results results;


void setup() {

Serial.begin(9600);
irrecv.enableIRIn();
pinMode(vccIR,OUTPUT);
pinMode(gndIR,OUTPUT);
pinMode(motorPIN,OUTPUT);
miServo.attach(servoPIN);
digitalWrite(vccIR,HIGH);
digitalWrite(gndIR,LOW);

}

void loop() {

if(irrecv.decode(&results))

    {

  Serial.println(results.value, HEX);



  switch (results.value){

      miServo.write(90);
      break;

      case 0xFD6897:  //dere
      miServo.write(40);
      break;

      case 0xFD28D7:  //izqui
      miServo.write(120);
      break;

      case 0xFDA857: // ok Enciende motor
      analogWrite(motorPIN,200);

      case 0xFD30CF:  // * Apaga motor
      miServo.write(120);
      analogWrite(motorPIN,0);
      break;
        }

     irrecv.resume();

    }
}
