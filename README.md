# Arduino Client Library for ESP8266 and ESP32

![arduino-library-badge](https://www.ardu-badge.com/badge/Firebase%20Arduino%20Client%20Library%20for%20ESP8266%20and%20ESP32.svg) ![PlatformIO](https://badges.registry.platformio.org/packages/mobizt/library/Firebase%20Arduino%20Client%20Library%20for%20ESP8266%20and%20ESP32.svg)


This library supports ESP8266 and ESP32 MCU from Espressif. The following are platforms in which the libraries are also available (RTDB only).


* [Arduino MKR WiFi 1010, Arduino MKR VIDOR 4000 and Arduino UNO WiFi Rev.2](https://github.com/mobizt/Firebase-Arduino-WiFiNINA)

* [Arduino WiFi Shield 101 and Arduino MKR1000 WIFI](https://github.com/mobizt/Firebase-Arduino-WiFi101)


 
## Other Arduino devices supported using external Clients.

Since version 3.0.0, library allows you to use external Arduino Clients network interfaces e.g. WiFiClient, EthernetClient and GSMClient, the Arduino supported devices that have enough flash size (> 128k) and memory can now use this library.

To use external Client, see the [ExternalClient examples](/examples/ExternalClient).

The authentication with OAuth2.0 and custom auth tokens, RTDB error queue and downloadFileOTA features are not supported for other Arduino devices using external Clients.

The flash and SD filesystems supports depend on the devices and third party filesystems libraries installed.


## Tested Devices

### This following devices were tested.

 * Sparkfun ESP32 Thing
 * NodeMCU-32
 * WEMOS LOLIN32
 * TTGO T8 V1.8
 * M5Stack ESP32
 * NodeMCU ESP8266
 * Wemos D1 Mini (ESP8266)
 * Arduino MKR WiFi 1010
 * LAN8720 Ethernet PHY
 * ENC28J60 SPI Ethernet module

### Supposted Arduino Devices with flash size > 128k, using custom Clients.

 * ESP32
 * ESP8266
 * Arduino SAMD
 * Arduino STM32
 * Arduino AVR
 * Teensy 3.1 to 4.1
 * Arduino Nano RP2040 Connect
 * Raspberry Pi Pico 



## Features




* **Supports external Heap via SRAM/PSRAM in ESP8266 and ESP32.**

* **Supports ethernet in ESP32 using LAN8720, TLK110 and IP101 Ethernet modules and ESP8266 using ENC28J60, W5100 and W5500 Ethernet modules.**



## Dependencies


This library required **ESP8266 or ESP32 Core SDK**.

ESP8266 Core SDK v2.5.0 and older versions are not supported.

For Arduino IDE, ESP8266 Core SDK can be installed through **Boards Manager**. 


### Manual installation

For Arduino IDE, download zip file from the repository (Github page) by select **Code** dropdown at the top of repository, select **Download ZIP** 

From Arduino IDE, select menu **Sketch** -> **Include Library** -> **Add .ZIP Library...**.

Choose **Firebase-ESP-Client-main.zip** that previously downloaded.

Rename **Firebase-ESP-Client-main** folder to **IOT-ASSITANT**.

Go to menu **Files** -> **Examples** -> **IOT-ASSITANT** and choose one from examples.

### Important Note for Manual Installation in Arduino IDE

Folder renaming to **IOT-ASSITANT** was required for making the library can be updated via Library Manager without problems.

Without folder renaming, when you update the library via Library Manager, library will be updated to the another folder named  **IOT-ASSITANT** which leads to compilation error when there are two different versions of library found in the libraries folder and can cause the conflicts when file structures and functions changed in the newer version. 

For example, the library version 1.0 and earlier were installed manually by downloading ZIP file and extracted to **IOT-ASSITANT** folder. If the library was later updated to v1.1 and newer via Library Manager, the compilation error will take place because the newer version files structures and functions changed and compiler is trying to compile these two versions of source files together. 

In this case, you need to delete **IOT-ASSITANT** folder from libraries folder.

## Usages


See [all examples](/examples) for complete usages.

See [function description](/src/README.md) for all available functions.