# Recupero e Visualizzazione dei Dati Ambientali

## Descrizione del Progetto

Questo progetto prevede l'uso di due **SparkFun Artemis RedBoard** con **Bluetooth Low Energy (BLE)** integrato. Un sensore **BME280** è collegato a una delle schede, mentre un **Micro OLED** è collegato all'altra. I dispositivi sono connessi tramite una connessione Bluetooth.

## Funzionamento

Il dispositivo con il sensore **BME280** acquisisce i dati ambientali, che vengono poi inviati all'altro dispositivo tramite Bluetooth per la visualizzazione sullo schermo.

## Dettagli Tecnici

- **Sensore BME280:** Utilizzato per raccogliere dati ambientali come temperatura, umidità e pressione atmosferica.
- **Micro OLED:** Utilizzato per visualizzare i dati ambientali ricevuti.
- **SparkFun Artemis RedBoard con BLE integrato:** Utilizzati sia per acquisire i dati dal sensore BME280 sia per visualizzarli sul Micro OLED.
- **Connessione Bluetooth:** Stabilisce una comunicazione senza fili tra i due dispositivi.

## Schema di Connessione

1. **Acquisizione Dati:**
   - Il sensore **BME280** raccoglie dati ambientali (temperatura, umidità, pressione).
   - I dati vengono inviati al **SparkFun Artemis RedBoard** tramite un'interfaccia I2C.

2. **Trasmissione Dati:**
   - Il **SparkFun Artemis RedBoard** con il sensore **BME280** invia i dati raccolti all'altro **SparkFun Artemis RedBoard** tramite **Bluetooth**.

3. **Visualizzazione Dati:**
   - Il **SparkFun Artemis RedBoard** ricevente elabora i dati ricevuti e li visualizza sul **Micro OLED** collegato tramite un'interfaccia SPI.

## Componenti Utilizzati

- **SparkFun Artemis RedBoard**
  - BLE integrato per comunicazione wireless
  - Microcontrollore potente e a basso consumo

- **Sensore BME280**
  - Misura temperatura, umidità e pressione
  - Alta precisione e bassa latenza

- **Display Micro OLED**
  - Schermo a basso consumo energetico
  - Alta risoluzione per una chiara visualizzazione dei dati

## Potenziali Applicazioni

- Monitoraggio ambientale in tempo reale
- Sistemi di automazione domestica
- Progetti di ricerca e sviluppo nel campo dell'IoT
