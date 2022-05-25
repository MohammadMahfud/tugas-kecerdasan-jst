#include <DHT.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define pinDHT 4
#define DHTTYPE DHT11
int pinLDR   = A0;
int pinM     = 11; //motor fan dc
int pinLED   = 10; //Lampu penerangan
int brightness = 0;
int fadeAmount = 5;
byte temperature = 0;
byte humidity = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(pinDHT_INPUT);
  pinMode(pinLDR_INPUT);
  pinMode(pinM_OUTPUT);
  pinMode(pinLED_OUTPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
 
}

void loop() {
  //////////////if statement suhu dan kelembaban
  lcd.clear();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  lcd.setCursor(0,0);
  lcd.print("Temp : ");
  lcd.print(t);
  lcd.print(" 'C");
  lcd.setCursor(0,1);
  lcd.print("Hum : ");
  lcd.print(h);
  lcd.print(" %");
  delay(1000);

  if (t < 32) {
    Serial.println("Too cold!");
    analogWrite(pinM, 50);
    delay (1000);
  }
  if (t > 32 && t < 35) {
    Serial.println("Perfect temperature!");
    analogWrite(pinM, 100);
    delay (2000);
  }
  if (t >= 35) {
    Serial.println("Too hot!");
    analogWrite(pinM, 200);
    delay (1000);
  }

/////////if statement Lampu pada Inkubator
  ldr=analogRead(pinLDR);

  if(nilai<273){
    analogWrite(led,255);
  }
  if(nilai>273 && nilai<300){
    analogWrite(led,150);
  }
  if(nilai>300){
    analogWrite(led,75);
  }
}
