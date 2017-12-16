#include <SoftwareSerial.h>
#include <SimpleDHT.h>

#define BLETx 10
#define BLERx 11
#define INA 5
#define LED 2
#define INB 6
#define DHTPIN 8

SoftwareSerial BLESerial(BLETx, BLERx);
String onoff;
char a;
SimpleDHT11 dht11;

void setup() {
  BLESerial.begin(9600);
  Serial.begin(9600);
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.println("Basic Serial Setting Success");
}

void loop() {
  byte temperature = 0;
  byte humidity = 0;
  if(dht11.read(DHTPIN, &temperature, &humidity, NULL)){
    Serial.print("DHT Error");
  }
  if(BLESerial.available()){
    a = BLESerial.read();
    if(a == '1') {
      Serial.println("ON");
      digitalWrite(LED, HIGH);
      digitalWrite(INA, HIGH);
      digitalWrite(INB, LOW);
    }
    else if(a == '0') {
      Serial.println("OFF");
      digitalWrite(LED, LOW);
      digitalWrite(INA, LOW);
      digitalWrite(INB, LOW);
    }
  }
  int t = (int)temperature;
  int h = (int)humidity;
  BLESerial.print(t);
  BLESerial.print(",");
  BLESerial.println(h);
  delay(1000);
}
