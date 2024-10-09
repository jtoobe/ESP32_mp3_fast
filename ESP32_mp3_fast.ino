// Tomado del ejemplo de la libreria DFPlayerMini_Fast

// hay que instalar la libreria ESPSoftwareSerial antes de poder compilar


#include <DFPlayerMini_Fast.h>

#if !defined(UBRR1H)
#include <SoftwareSerial.h>
// 26 va al pin RX del mp3, 27 al pin TX del mp3
// se pueden definir otros pines del ESP32 para este uso
SoftwareSerial mySerial(27, 26); 
#endif

DFPlayerMini_Fast myMP3;

void setup()
{
  Serial.begin(115200);

#if !defined(UBRR1H)
  mySerial.begin(9600);
  myMP3.begin(mySerial, true);
#else
  Serial1.begin(9600);
  myMP3.begin(Serial1, true);
#endif
  
  delay(1000);
  
  Serial.println("Setting volume to max");
  myMP3.volume(30);  // mas de 30 no va.
  
  Serial.println("Looping track 1");

  // reproduce el PRIMER archivo mp3 que encuentra en el directorio raiz de la SD
  
  myMP3.loop(1);
}

void loop()
{
  //do nothing
}
