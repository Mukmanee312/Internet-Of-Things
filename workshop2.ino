/* Workshop2 การอ่านค่าจากเซนเซอร์วัดความชื้นดิน
และเซนเซอร์ DHT 
*/

#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN D5
#define DHTTYPE DHT22
#define Soilpin A0
#define water_pump LED_BUILTIN
#define Fan D2
//ประกาศตัวแปร แบบ Global Variable
float Temp, Humi;
int soil_value, percent;

// ประกาศ object สำหรับ DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(DHTPIN, INPUT);
  pinMode(Soilpin, INPUT);
  pinMode(water_pump, OUTPUT);
  pinMode(Fan, OUTPUT);
  dht.begin();
  delay(2000);
}

void loop() {
  Temp = dht.readTemperature();
  Humi = dht.readHumidity();
  //อ่านค่าความชื้นดิน อุณหภูมิ ความชื้นในอากาศ
  soil_value = analogRead(Soilpin);
  percent = map(soil_value, 0, 1023, 100, 0);

  if (isnan(Temp) || isnan(Humi)) {
    Serial.print("Fail to read sensor");
    return;
  }
  Serial.printf("Temperature  = %.2f °C\tHumidity = %.2f %%\n", Temp, Humi);
  Serial.printf("Soil Value  = %d\tSoil in percent = %d %%\n", soil_value, percent);

  //ตรวจสอบเงื่อนใขความชื้นในดิน และ อุณหภูมิในอากาศ
  if (percent < 45) {
    Serial.println("ความชื้นในดินต่ำเกินไป ควรให้นำเพิ่มเติม");
    digitalWrite(water_pump, LOW);
  } else {
    digitalWrite(water_pump, HIGH);
  }
  if (Temp >= 32) {
    Serial.println("อุณหภูมิสูงเกินไป ต้องเปิดระบบระบายอากาศ");
    digitalWrite(Fan, HIGH);
  }else{
    Serial.println("อุณหภูมิอยู่ในช่วงปรกติ");
    digitalWrite(Fan, LOW);
  }
  Serial.println();
  delay(3000);
}
