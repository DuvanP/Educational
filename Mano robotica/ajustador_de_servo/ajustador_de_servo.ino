 // incluimos la libreria del servomotor
 #include <Servo.h>

   // Le indicamos a la libreria que vamos a usar
  // un solo servomotor.
Servo myservo5;

void setup() {
  // put your setup code here, to run once:
    myservo5.attach(5);

}

void loop() {
  myservo5.write(180);              // tell servo to go to position in variable 'pos'


}
