
int PinSensorflex = A0; // indicamos el pin del sensor

int LecturaSensorflex;  // Acá guardaremos los datos del sensor

int puntaje_alto = 1024; // Nivel Alto del sensor

int puntaje_bajo = 0; // Nivel Bajo del sensor

int Mapeo;              // Acá guardaremos los datos del 
                        // sensor mapeados

            
void setup(){
Serial.begin(9600); // iniciamos la comunicación con arduino
}

void loop(){

LecturaSensorflex = analogRead(PinSensorflex); // Leemos el Sensor flexible

Mapeo = map(LecturaSensorflex, puntaje_bajo , puntaje_alto,0, 250); // hacemos el mapeo

Serial.print("Lectura Sensor  "); // imprimimos en el puerto serial la información
Serial.print(LecturaSensorflex);

Serial.print("  Lectura mapeado   ");
Serial.println(Mapeo);

analogWrite(3,Mapeo); // Prendemos el Led dependiendo de cuanto flexionamos el dedo


}
