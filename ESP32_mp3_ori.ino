/***************************************************

Tomado del ejemplo de la libreria original del MP3-TF-16P
DFRobotDFPlayerMini que se instala desde la IDE de Arduino
es el reproductor que se vende en ML.

Script modificado para que sea mas sencillo de implementar en ESP32

hay que instalar la libreria ESPSoftwareSerial antes de poder compilar

 ****************************************************/

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Se pueden usar pines distintos a los propuestos
static const uint8_t PIN_MP3_TX = 26;  // 26 => Mp3 RX
static const uint8_t PIN_MP3_RX = 27;  // 27 => Mp3 TX
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// Create the Player object
DFRobotDFPlayerMini player;

void printDetail(uint8_t type, int value);

void setup() {

  // Init USB serial port for debugging
  Serial.begin(115200);
  // Init serial port for DFPlayer Mini
  softwareSerial.begin(9600);

  // Start communication with DFPlayer Mini
  if (player.begin(softwareSerial)) {
    Serial.println("OK");

    // Set volume to maximum (0 to 30).
    player.volume(20);
    // Play the first MP3 file on the SD card
    // player.play(1);
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
    Serial.println("Esperar.... (No siempre es correcto este mensaje)");
  }
}

void loop() {

  // Una forma simple de ejecutar mp3
  // player.play(random(1, 3));
  // delay(10000); // Este delay tiene que ser mayor a la duracion del MP3


  static unsigned long timer = millis();

  if (millis() - timer > 5000) {
    timer = millis();
    player.next();  //Play next mp3 every 3 second. 
    // nota: para las pruebas puse un archivo 001.mp3 en la raiz de la SD
    // y otro distinto tambien llamado 001.mp3 en una carpeta llamada "mp3"
    // el script los reproduce secuencialmente 
  }

  if (player.available()) {
    printDetail(player.readType(), player.read());  //Print the detail message from DFPlayer to handle different errors and states.
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
