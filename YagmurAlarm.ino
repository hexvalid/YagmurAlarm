#include <virtuabotixRTC.h>
int TMP_hour;


//ALARM AYARI!
int ALR_hour = 6;
int ALR_minute = 55;
boolean ALR_STS = false;
//

// Creation of the Real Time Clock Object
//SCLK -> 6, I/O -> 7, CE -> 8
virtuabotixRTC myRTC(6, 7, 8);
const int BIGbuzzer =  4;
const int REDled =  13;
const int PUSHbutton =  10;
void setup() {
  Serial.begin(9600);
  pinMode(BIGbuzzer, OUTPUT);
  pinMode(REDled, OUTPUT);
  pinMode(PUSHbutton, INPUT_PULLUP);


  // Set the current date, and time in the following format:
  // seconds, minutes, hours, day of the week, day of the month, month, year
  // myRTC.setDS1302Time(20, 17, 00, 5, 24, 6, 2015);
}

void loop() {
  // This allows for the update of variables for time or accessing the individual elements.

  // Her saat başında bir bipbip etmeye yarar.
  myRTC.updateTime();
  if (myRTC.hours != TMP_hour)
  {
    bipbip();
  }
  TMP_hour = myRTC.hours;


  //Alarmı kontrol et
  if (myRTC.hours == ALR_hour && myRTC.minutes == ALR_minute && ALR_STS == false) {
    Serial.println("Alarm başladı");
    digitalWrite(BIGbuzzer, HIGH);
    if (digitalRead(PUSHbutton) == LOW) {
      digitalWrite(BIGbuzzer, LOW);
      Serial.println("Alarm durdu");
      ALR_STS = true;
    }

  }


  // Start printing elements as individuals
  Serial.print("Tarih / Saat: ");
  Serial.print(myRTC.dayofmonth);
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print(" ");
  Serial.print(myRTC.hours);
  Serial.print(":");
  Serial.print(myRTC.minutes);
  Serial.print(":");
  Serial.println(myRTC.seconds);

  // Delay so the program doesn't print non-stop
  delay( 1000);
}

void bipbip() {
  digitalWrite(BIGbuzzer, HIGH);
  delay(100);
  digitalWrite(BIGbuzzer, LOW);
  delay(100);
  digitalWrite(BIGbuzzer, HIGH);
  delay(100);
  digitalWrite(BIGbuzzer, LOW);
}




