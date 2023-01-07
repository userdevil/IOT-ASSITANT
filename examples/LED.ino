#include <Arduino.h>
#include <WiFi.h>
#include <Iot_assistant.h>
#include <Wire.h>
#include "time.h"

// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL ""
#define USER_PASSWORD ""


// Define Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Variable to save USER UID
String uid;

// Database main path (to be updated in setup with the user UID)
String databasePath;
// Database child nodes
String Path = "/status";

// Parent Node (to be updated in every loop)
String parentPath;

FirebaseJson json;


// Initialize WiFi
void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}

void setup(){
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  initWiFi();
  

  // Assign the api key (required)
  config.api_key = API_KEY;

  // Assign the user sign in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  // Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  // Assign the maximum retry of token generation
  config.max_token_generation_retry = 5;

  // Initialize the library with the Firebase authen and config
  Firebase.begin(&config, &auth);

  // Getting the user UID might take a few seconds
  Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }
  // Print user UID
  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.println(uid);

  // Update database path
  databasePath = "/UserData/" + uid + "/Control";
}

void loop(){

  // Send new readings to database
  if (Firebase.ready()){
    String p = databasePath + Path;
    Serial.printf("Get string... %s\n", Firebase.RTDB.getString(&fbdo,p.c_str()) ? fbdo.to<const char *>() : fbdo.errorReason().c_str());
    String state = Firebase.RTDB.getString(&fbdo,p.c_str()) ? fbdo.to<const char *>() : fbdo.errorReason().c_str();
    if(state == "LED on"){
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("led on");
    }
    if(state == "LED off"){
      digitalWrite(LED_BUILTIN, LOW);
    }
  delay(5000);
    }
 }