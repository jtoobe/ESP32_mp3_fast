/***************************************************

Tomado del ejemplo de la libreria original del MP3-TF-16P
DFRobotDFPlayerMini que se instala desde la IDE de Arduino
es el reproductor que se vende en ML.

Script modificado para que sea mas sencillo de implementar en ESP32

hay que instalar la libreria ESPSoftwareSerial antes de poder compilar

 ****************************************************/


#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>
// 26 va al pin RX del mp3, 27 al pin TX del mp3
// se pueden definir otros pines del ESP32 para este uso
SoftwareSerial FPSerial(27, 26);


DFRobotDFPlayerMini myDFPlayer;


void setup() {

  Serial.begin(115200);


  FPSerial.begin(9600);
  myDFPlayer.begin(FPSerial, true);

  Serial.begin(115200);


  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
}

void loop() {

  // reproduce secuencialmente todas las pista sin improtar en que carpeta estan
  //myDFPlayer.next();
  //delay(10000);

  // reproduce solo la pista 3 no importa la carpeta
  //myDFPlayer.play(3);
  //delay(20000);

  // reproduce aleatoriamente todo
  myDFPlayer.randomAll();
  delay(10000);

  // es importante el delay despues de enviar la orden de ejecucion, puesto
  // que si enviamos otra orden a continuacion "corta" lo que esta reproduciendo
  // y ejecuta lo nuevo


}
