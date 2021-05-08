#include <DHT.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);

#define no_dust 0.35;

DHT dht1(10, DHT11); //외부 온도
DHT dht2(9, DHT11);  // 내부 온도

int fus = 13; //불꽃감지센서
int gs = A0;  //가스센서

int vo = A1;
int s_led = 5;
float val = 0;
float volt = 0;
float dustDensity = 0;

float sensor_volt1;
float sensor_volt;
float R0;
float RS_air;
float ratio;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(fus, INPUT);
  pinMode(gs, INPUT);
  pinMode(s_led, OUTPUT);
  pinMode(vo, INPUT);

  Serial.println("잠시 기다려주세요");
  delay(1000);
}

int Flame = digitalRead(fus);
int ot;
int oh;
int it;
int ih;
int gas;
bool fire;
bool gas_full;

void loop() {

  //-----외부 온도 측정-----
  ot = dht1.readTemperature();
  oh = dht1.readHumidity();
  //-----내부 온도 측정-----
  it = dht2.readTemperature();
  ih = dht2.readHumidity();

  //-----오차 값-----
  int at = ot - it;
  int ah = oh - ih;

  int nt = it - 18;
  int nh = ih - 40;

  //미세먼지 센서 측정

  digitalWrite(s_led, LOW);
  delayMicroseconds(280);

  val = analogRead(vo);
  delayMicroseconds(40);

  digitalWrite(s_led, HIGH);
  delayMicroseconds(9680);

  volt = val * 5.0 / 1024.0;
  dustDensity = (volt - 0.3) / 0.005;
  Serial.print("전압 = ");
  Serial.println(volt);
  Serial.print("먼지 밀도 = ");
  Serial.println(dustDensity);

  //가스 센서 측정
  for (int i = 0; i < 10000; i++) {
    sensor_volt1 = sensor_volt + analogRead(A0);
  }
  sensor_volt1 = sensor_volt1 / 100.0;

  sensor_volt = sensor_volt1 / 1024 * 5.0;
  RS_air = (5.0 - sensor_volt) / sensor_volt;
  R0 = RS_air / 6.5;

  //////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////

  Serial.println("================================================");

  Serial.print("평균 온도값 오차 : ");
  Serial.println(nt);
  Serial.print("평균 습기값 오차 : ");
  Serial.println(nh);

  Serial.print("외.내부 온도값 오차 : ");
  Serial.println(at);
  Serial.print("외.내부 습기값 오차 : ");
  Serial.println(ah);

  //온도 평균
  Serial.print("온도 상황: ");
  if (at >= -10) {
    Serial.println("온도 매우 낮음");
    mySerial.write("Ha");
  }
  else if (at >= 10) {
    Serial.println("온도 매우 높음");
    mySerial.write("Hb");
  } else if (at <= 5) {
    Serial.println("온도 정상");
    mySerial.write("Hc");
  }
  delay(100);
  
  //불꽃 감지
  Serial.print("불꽃 감지 상황: ");
  if (Flame == HIGH) {
    Serial.println("불꽃 감지");
    mySerial.write("Fa");
    fire = true;
  } else {
    Serial.println("불꽃 감지 안됨");
    mySerial.write("Fb");
    fire = false;
  }
  delay(100);
  
  //미세먼지 농도
  Serial.print("미세먼지 상황 : ");
  if (dustDensity <= 50) {
    Serial.println("좋음");
    mySerial.write("Da");
  } else if (dustDensity <= 80) {
    Serial.println("보통");
    mySerial.write("Db");
  } else if (dustDensity <= 150) {
    Serial.println("나쁨");
    mySerial.write("Dc");
  } else if (dustDensity > 150) {
    Serial.println("매우 나쁨");
    mySerial.write("Dd");
  }
  Serial.print("Dust Density = ");
  Serial.print(dustDensity);
  Serial.println(" [ug/m^3]");
  delay(100);

  // 가스 누출
  Serial.print("가스 누출 상태 : ");
  if (R0 >= 40) {
    Serial.println("가스 확인");
    mySerial.print("Ga");
    gas_full = true;
  } else if (R0 <= 41) {
    Serial.println("가스 미노출");
    mySerial.print("Gb");
    gas_full = false;
  }
  Serial.println(R0);
  delay(100);

  Serial.print("가스노출 : ");
  Serial.println(gas_full);
  Serial.print("불꽃감지");
  Serial.println(fire);
  Serial.print("결론 : ");
  if (gas_full == true && fire == true) {
    Serial.println("화제 발생");
  } else if (gas_full == false && fire == false) {
    Serial.println("고요한 집임");
  }

delay(200);
}
