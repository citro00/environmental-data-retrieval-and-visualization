#include <ArduinoBLE.h>
#include <Wire.h>
#include "SparkFunBME280.h"
//inizializzazione costanti bluetooth
const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";
//variabile sensore
BME280 mySensor;
int Environment[4];//Inizializzazione Array dati ambiente

 void setup()
 {
            Wire.begin();
            Serial.begin(9600);
            Serial.println("Inizializzazione Sensore BME280");
            Serial.println();
      if (mySensor.beginI2C() == false)
            {
            Serial.println("Il sensore non risponde si prega di collegare il cablaggio ");
            }
             Serial.begin(9600);
     if (!BLE.begin())  
         {
          Serial.println("Avvio del modulo Bluetooth  non riuscito!");
         }
          BLE.setLocalName("Spark fun Artemis(Central)"); 
          Serial.println();
          BLE.advertise();
          Serial.println("Spark fun Artemis (dispositivo centrale)");
          Serial.println();
 }

 void loop() 
 { 
  connectToPeripheral();
 }

 void connectToPeripheral()
 {
           BLEDevice peripheral;
           Serial.println("Sto cercando il dispositivo periferico...");
           Serial.println();
           delay(4000);
         do
       {
         BLE.scanForUuid(deviceServiceUuid);
         peripheral = BLE.available();
       } while (!peripheral);
  
          if (peripheral) 
             {
               Serial.println("Dispositivo Periferico Trovato");
               Serial.println();
               Serial.print("MAC address del dispositivo: ");
               Serial.println(peripheral.address());
               Serial.println();
               Serial.print("Codice UUID: ");
               Serial.println(peripheral.advertisedServiceUuid());
               Serial.println();
               BLE.stopScan();
               controlPeripheral(peripheral);
             } else Serial.println("Errore di connessione");
 }

 void controlPeripheral(BLEDevice peripheral) 
 {
    Serial.println("Collegamento al dispositivo periferico...");
    Serial.println();
      if (peripheral.connect()) 
      {
         Serial.println(" Connesso al dispositivo periferico!");
         Serial.println();
      } else {
               Serial.println("Connessione al dispositivo periferico non risucita!");
               Serial.println();
               return;
              }
                Serial.println("Analisi degli attributi del dispositivo periferico..");
                Serial.println();
                if (peripheral.discoverAttributes()) 
                {
                   Serial.println("attributi analizzati!");
                   Serial.println();
                }  else {
                          Serial.println("Analisi degli attributi del dispositivo periferico fallita!");
                          Serial.println();
                          peripheral.disconnect();
                           return;
                        }

                        BLECharacteristic send = peripheral.characteristic(deviceServiceCharacteristicUuid);
    
           if (!send) 
               {
                 Serial.println("*Errore non ci sono dati da inviare!");
                 peripheral.disconnect();
                  return;
                } else if (!send.canWrite())
                    {
                       Serial.println("* Non si possono inviare dati al dispositivo periferico!");
                       peripheral.disconnect();
                       return;
                    }
         while (peripheral.connected()) 
              {
                EnvironmentalData();
                for(int i=0;i<=3;i++)
                send.writeValue((byte)Environment[i]);
              }
  Serial.println("Dispositivo di periferia disconnesso!");
 }
//Prelevo i dati con il sensore
void EnvironmentalData()
 {
   Environment[0]=(int)mySensor.readFloatHumidity();
   Environment[1]=(int)mySensor.readFloatPressure();
   Environment[2]=(int)mySensor.readFloatAltitudeFeet();
   Environment[3]=(int)mySensor.readTempC();
}