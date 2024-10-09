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
void printDetail(uint8_t type, int value);

void setup() {

  Serial.begin(115200);


  FPSerial.begin(9600);
  myDFPlayer.begin(FPSerial, true);




  Serial.begin(115200);


  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);     //Play the first mp3
}

void loop() {
  static unsigned long timer = millis();

  if (millis() - timer > 5000) {
    timer = millis();
    myDFPlayer.next();  //Play next mp3 every 3 second. 
    // nota: para las pruebas puse un archivo 001.mp3 en la raiz de la SD
    // y otro distinto tambien llamado 001.mp3 en una carpeta llamada "mp3"
    // el script los reproduce secuencialmente 
  }

  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read());  //Print the detail message from DFPlayer to handle different errors and states.
  }
}

void printDetail(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}