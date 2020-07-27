//필요한 라이브러리 포함
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <FirebaseArduino.h>
#include <DHT.h>
#include <time.h>

//Firebase 호스트,db키 값 입력
#define FIREBASE_HOST "hello-firebase-17515.firebaseio.com"
#define FIREBASE_AUTH "GHvkB3lxoyultkoie8vUcO0Cf6nu22EDvxTByrc9"

//와이파이 아이디와 비밀번호 입력
#define WIFI_SSID "netis"
#define WIFI_PASSWORD "alswn1121"

// Config DHT
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

WiFiUDP udp;
//NodeMCU 날짜, 시간 구하기
NTPClient timeClient(udp, "kr.pool.ntp.org", 32400, 3600000);

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.mode(WIFI_STA);  // Wi-Fi 초기화 
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting......");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  //시간을 얻기 위해 NTPClinet 초기화
  timeClient.begin();

  // Firebase에 연결 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  delay(5000);

  //온습도 값을 읽어온다
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  //옵습도 값을 읽어오지 못했다면
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(500);
    return;
  }
  //시간 업데이트
  timeClient.update();

//  int hour = timeClient.getHours();
//  int minute = timeClient.getMinutes();
//  int second = timeClient.getSeconds();
  //시간을 얻어온다
  unsigned long epochTime = timeClient.getEpochTime();

  struct tm *ptm = gmtime ((time_t *)&epochTime); 
  
  int currentMonth = ptm->tm_mon+1;
  int monthDay = ptm->tm_mday;
  int currentYear = ptm->tm_year+1900;
  //년도, 월, 일 값을 받아옴
  String currentDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);
  String currentTime = timeClient.getFormattedTime();
 
  String currentDateTime = currentDate + " " + currentTime;
  
//  Serial.println(timeClient.getFormattedTime());
//  Serial.println(currentDate);
//  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("   Temperature: ");
  Serial.print(t);
  Serial.print("   Time: ");
  Serial.print(currentDateTime);

  //json 변환에 필요한 버퍼인 staticjsonbuffer을 선언하고 용량을 설정한다 //200은 버퍼크기
  StaticJsonBuffer<200> jsonBuffer; 
  //JsonObject를 선언하여 json형식을 만들어 낼 수 있는 객체를 선언한다
  JsonObject& root = jsonBuffer.createObject();
  //key값을 설정 하고 value를 지정한다
  root["temperature"] = t;
  root["humidity"] = h;
  //root["time"] = hour;
  root["time"] = currentDateTime;
  
  // /logDHT 아래에 온도와 습도값이 append된다
  String name = Firebase.push("logDHT", root);
  // handle error
  if (Firebase.failed()) {
      Serial.println("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.println("");
  Serial.print("   pushed: /logDHT/");
  Serial.println(name + "\n");
  delay(5000);
}
