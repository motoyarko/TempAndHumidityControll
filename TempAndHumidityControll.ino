#include <dht.h>
#include <TM1637Display.h>
#include <Arduino.h>

#define ClkDisplay 3
#define DioDisplay 2
#define DhtPin 5

TM1637Display display(ClkDisplay, DioDisplay);
dht sensor;


const uint8_t SegCelsius[] = {
  SEG_A | SEG_B | SEG_G | SEG_F, //o
  SEG_G | SEG_E | SEG_D  //c
  };

const uint8_t SegHumidity[] = {
  SEG_A | SEG_B | SEG_G | SEG_F, //o
  SEG_F | SEG_E | SEG_G | SEG_C  //h
  };

void setup() {
  pinMode(13, OUTPUT);
  pinMode(4, INPUT); //vape tank is full = HIGH
  
  pinMode(9, OUTPUT);//ON/OFF vape mashine
  pinMode(8, OUTPUT);//ON/OFF heating
  pinMode(7, OUTPUT);//ON/OFF Water pump
    
  display.setBrightness(0xff);
  uint8_t fullDisplay[] = { 0xff, 0xff, 0xff, 0xff };
  uint8_t blankDisplay[] = { 0, 0, 0, 0 };
  
  //test all segments of display
  display.setSegments(fullDisplay);
  delay(500);
  display.setSegments(blankDisplay);
}

void timer(int counter) {
   for (int i=0; i <= counter * 9999999999; i++);
}
  
void loop() {
  int checkSensor = sensor.read11(DhtPin);
  int temp = sensor.temperature;
  int humidity = sensor.humidity;

  if (digitalRead(4) == HIGH) {
    digitalWrite(13, HIGH);
  }
 
 if (checkSensor == DHTLIB_OK)
  {
   display.showNumberDec(temp, false, 2, 0);
   display.setSegments(SegCelsius, 2, 2);
   //Serial.print(temp);
   timer(10000);
   display.showNumberDec(humidity, false, 2, 0);
   display.setSegments(SegHumidity, 2, 2);
   //Serial.println(humidity);
   timer(2000000000000);
  }

}
