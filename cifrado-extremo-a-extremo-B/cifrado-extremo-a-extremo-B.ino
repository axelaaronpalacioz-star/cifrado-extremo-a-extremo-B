#include <SoftwareSerial.h>
 
const byte llaveXOR = 0b00000100;
SoftwareSerial enlace(10, 11); // RX, TX
 
void setup() {
  Serial.begin(9600);
  enlace.begin(9600);
  Serial.setTimeout(1000);
 
  Serial.println("ARDUINO B - COMUNICACION XOR");
  Serial.println("Escribe un mensaje y presiona Enter.");
}
 
void loop() {
  // Enviar mensaje cifrado
  if (Serial.available() > 0) {
    String original = Serial.readStringUntil('\n');
    original.trim();
 
    if (original.length() > 0) {
      String cifrado = "";
 
      for (unsigned int i = 0; i < original.length(); i++) {
        byte letra = (byte)original[i] ^ llaveXOR;
        cifrado += (char)letra;
      }
 
      Serial.print("Mensaje original: ");
      Serial.println(original);
 
      Serial.print("Mensaje cifrado enviado: ");
      Serial.println(cifrado);
 
      enlace.println(cifrado);
    }
  }
 
  // Recibir y descifrar mensaje
  if (enlace.available() > 0) {
    String recibido = enlace.readStringUntil('\n');
    recibido.trim();
 
    String descifrado = "";
 
    for (unsigned int i = 0; i < recibido.length(); i++) {
      byte letra = (byte)recibido[i] ^ llaveXOR;
      descifrado += (char)letra;
    }
 
    Serial.print("Mensaje cifrado recibido: ");
    Serial.println(recibido);
 
    Serial.print("Mensaje descifrado: ");
    Serial.println(descifrado);
    Serial.println("-------------------------");
  }
}
