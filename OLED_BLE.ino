#include <ArduinoBLE.h>
#include <Wire.h>
#include <SFE_MicroOLED.h> 

//inizializzazione e settaggio Schermo Oled
#define PIN_RESET 9
#define DC_JUMPER 1
MicroOLED oled(PIN_RESET, DC_JUMPER);
const int buttonPin = 2;
const int ledPin =  13;
//inizializzazione costanti Bluetooth
const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214"; 

int Environment[4];//inizializzazione array ambiente
BLEService bleService(deviceServiceUuid); 
BLEByteCharacteristic bleCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite);


 void setup() 
  {
        BLE.begin();
        Wire.begin();
        delay(100);
        oled.begin();
        oled.clear(ALL);
        oled.display();
        delay(1000);
        oled.clear(PAGE);
        oled.display();
        oled.setFontType(0);
        oled.setCursor(0,0);
        pinMode(ledPin, OUTPUT);
        pinMode(buttonPin, INPUT_PULLUP);
        Serial.begin(9600);

    if (!BLE.begin()) 
         {
          Serial.println("Avvio del modulo Bluetooth non riuscito!");
          Serial.println();
         }
            BLE.setLocalName("Artemis Sparkfun Read Board (Dispositivo Periferico)");
            Serial.println();
            BLE.setAdvertisedService(bleService);
            bleService.addCharacteristic(bleCharacteristic);
            BLE.addService(bleService);
            BLE.advertise();
            Serial.println("Artemis Sparkfun Read Board (Dispositivo Periferico)");
            Serial.println();
 }

 void loop() 
 {
   BLEDevice central = BLE.central();
   Serial.println("Sto cercando il disposito centrale...");
   Serial.println();
   delay(500);

    if (central) 
    {
         Serial.println("Connessione al dispositivo centrale!");
         Serial.println();
         Serial.print("MAC address del dispositivo : ");
         Serial.println(central.address());
         Serial.println();
         int i =0;
         while (central.connected())
         {
            if (bleCharacteristic.written()) 
              {
                Environment[i]= bleCharacteristic.value();
                 i++;
              }
                if (i==4)
                { //visualizzazione su Schermo Oled
                   oled.clear(PAGE);
                   oled.display();
                   oled.setCursor(0,0);
                   i=0;
                   oled.print("Umi: ");//umidità
                   oled.println(Environment[0]);
                   oled.print("Pres: ");//Pressione
                   oled.println(Environment[1]);
                   oled.print("Alt: ");//Altitudine
                   oled.println(Environment[2]);
                   oled.print("Temp: ");//Temperatura
                   oled.println(Environment[3]);     
                   oled.display();
                }
     
         } Serial.println("Disconnessione del dispositivo Centrale!");
    }
 }