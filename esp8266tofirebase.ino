#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>

#define ssid "Student_Polban"  //WiFi SSID   // BUTUH WIFI MANAGER
#define password "wifi_polban"  //WiFi Password
#define DATABASE_URL "ir-firebass-demo-default-rtdb.asia-southeast1.firebasedatabase.app"
#define DATABASE_SECRET "W9HCXqjT4F4CrEbja3bRiCis0ORqdDSafA7ZFBNQ"

FirebaseData fbdo;

// VARIABEL PIN
const int IRpin = 16; //D0
const int LEDpin = 5; //D1

// VARIABEL TAMBAHAN
int count = 0, firebaseCount;
bool state;

//SETUP
void setup(){

  // SERIAL
  Serial.begin(9600);
  
  // KONEK WIFI
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
}

// SET PIN 
pinMode(IRpin, INPUT);
pinMode(LEDpin, OUTPUT);

// INISIALISASI FIREBASE 
Firebase.reconnectWiFi(true);
Firebase.begin(DATABASE_URL, DATABASE_SECRET);

}

// LOOP
void loop(){
  CheckIR();
  AmbilCountDariFirebase();
  delay(50);
}

void CheckIR(){
  // KALO PIN IR BACA SESUATU
  if(!digitalRead(IRpin) && state){
    count++;
    state = false;
    digitalWrite(LEDpin, HIGH);
    delay(100);
    
    // UPLOAD VALUE COUNT KE FIREBASE
    Firebase.setInt(fbdo, F("/COUNT"), count) ? "ok" :
    fbdo.errorReason().c_str();
  }

  if(digitalRead(IRpin)){
    state = true;
    digitalWrite(LEDpin, LOW);
    delay(100);
  }
}

void AmbilCountDariFirebase() {

    // AMBIL VALUE /COUNT DARI FIREBASE
    Firebase.getInt(fbdo, F("/COUNT")); firebaseCount = fbdo.intData(); fbdo.errorReason().c_str();

    Serial.print("Count: ");
    Serial.println(firebaseCount);
}
