#include "DHT.h"

#define DHTPIN 16     // Conectamos el pin analogo A2 que es el
                      // mismo pin 16 digital

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  
  Serial.begin(9600);  // Iniciamos el puerto serial a 9600 bps
  Serial.println("DHT11 test!"); // imprimimos el mensaje "DHT11 test!" en el
                                 // monitor serial

  dht.begin();  // Habilitamos la obtención de datos del sensor DHT11
}

void loop() {
  // esperamos 2 segundos mientras el sensor hace la medición
  delay(2000);


  float h = dht.readHumidity(); // Guardamos en la variable h el valor 
                                // de la humedad relativa 
  
  float t = dht.readTemperature(); // Guardamos en la variable t el valor
                                   // de la temperatura 

  // Verificamos que la medicion sea exitosa, si no lo es 
  // mostrará el mensaje " No se detecta el sensor DHT11"
  if (isnan(h) || isnan(t)) {
    Serial.println("No se detecta el sensor DHT11!");
    return;
  }
        // imprimimos los siguientes mensajes en el puerto serial

  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");

}
