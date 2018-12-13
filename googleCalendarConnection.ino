/* Event calendar display using Google Calendar and Google scripts for NODE-MCU & 20x4 LCD 
   Created by Seweryn Talaj, 2018  github.com/Seweryn91
   
   Based on code by Daniel Willi  github.com/wilda17:
   https://github.com/wilda17/ESP8266-Google-Calendar-Arduino
   
   */

#include <ESP8266WiFi.h>
#include <time.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "HTTPSRedirect.h"


//Connection settings
const char* ssid = "SSID"; //WiFi SSID
const char* password = "PASSWORD"; //WiFi password
const char* GScriptId = "GOOGLE SCRIPT ID"; //Google script ID


//Google Scripts setup
const char* host = "script.google.com";
const char* googleRedirHost = "script.googleusercontent.com";
const int httpsPort = 443;
const int maxStringLen = 20; //Maximum length of line that can be printed on 20x4 LCD
String url = String("/macros/s/") + GScriptId + "/exec";
const String delimeter = "\n"; //Delimiter for Events
int interval = 0; //interval counter that is used to connect with google every 30 seconds;

//LCD setup
LiquidCrystal_I2C lcd(0x27, 20, 4); //address and resolution of LCD

//Time and date setup
int timezone = 1; //set your timezone
int dst = 0; //daylight saving time


void setup() {
  //LCD SETUP
  Wire.begin(2, 0); // Pins SDA D4, SCL D3
  lcd.init();   // Initializing the LCD
  lcd.backlight(); // Enabling backlight on LCD

  Serial.begin(9600);
  //Serial.setDebugOutput(true); //Uncomment to get debug output on Serial monitor.

  //CONNECTION SETUP
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  lcd.print("Connecting to WiFi:");
  lcd.setCursor(0, 1);
  lcd.print(ssid);

  //WAIT FOR CONNECTION
  while (WiFi.status() != WL_CONNECTED) {
    lcd.setCursor(0, 2);
    lcd.print("Please wait...");
    delay(1000);
  }

  //TIMER SETUP
  configTime(timezone * 3600, dst, "pool.ntp.org", "time.nist.gov");
  while (!time(nullptr)) {
    Serial.print(".");
    lcd.clear();
    delay(1000);
  }
}

void loop() {
  clearLine(0);
  getCurrentTimeFromRouter();

  if (interval == 0) {
    printCalendar();
  } else if (interval > 4) {
    interval = -1;
  }
  interval++;

  Serial.println("");
  delay(5000); //wait 5 seconds
}


void getCurrentTimeFromRouter() {
  clearLine(0);
  Serial.println("\nWaiting for time");
  char s[18];
  time_t temp = time(NULL);
  struct tm *timeptr;
  timeptr = localtime(&temp);

  int rc = strftime(s, sizeof(s), "%a, %b %d %R", timeptr);
  lcd.setCursor(0, 0);
  lcd.printf("%s", s);
  Serial.println("");
  Serial.printf("%s", s);
  Serial.println("");
}


//Get entries data through Google Script
String fetchDataFromGoogle() {

  HTTPSRedirect client(httpsPort);
  if (!client.connected()) {
    Serial.println("Connecting with Google");
    client.connect(host, httpsPort);
  }

  String data = client.getData(url, host, googleRedirHost);
  Serial.println(data);

  return data;
}

void printCalendar() {
  clearLine(1);
  clearLine(2);
  displayAuthor(2);
  clearLine(3);

  String calendarData = fetchDataFromGoogle(); //get data from Google Calendar
  int firstLineTerminationIndex = calendarData.indexOf('\n');
  String firstLine = calendarData.substring(0, firstLineTerminationIndex); //substring to first newline without null-character (\n)

  printOnLCD(0, 1, firstLine);
  if (firstLine == "No events scheduled " || firstLine == "error" ||  firstLine == "~Connection error" || firstLine == "~Re-direct error") {
    clearLine(2);
    clearLine(3);
  } else {
    int secondLineTerminationIndex = calendarData.indexOf('\n', firstLineTerminationIndex + 1);
    String secondLine = calendarData.substring(firstLineTerminationIndex + 1, secondLineTerminationIndex);
    
      if (secondLine.length() < maxStringLen) { //If response length is no longer than max length of displayable string
        clearLine(2); //clear link to my github ;) Not needed if method displayAuthor() is never used.
        printOnLCD(0, 2, secondLine);
      } else {
        String shortenedLine = secondLine.substring(0, 17) + "...";
        printOnLCD(0, 2, shortenedLine);
      }
      int thirdLineTerminationIndex = calendarData.indexOf('\n', secondLineTerminationIndex + 1);
      String thirdLine = calendarData.substring(secondLineTerminationIndex + 1, thirdLineTerminationIndex);

      if (thirdLine.length() > 2) {
        printOnLCD(0, 3, thirdLine);
      } else {
        clearLine(3);
      }
  }
}

void clearLine(int row) {
  lcd.setCursor(0, row);
  lcd.print("                    "); //20 times whitespace because LCD row is 20 chars max length.
}

void printOnLCD(int col, int row, String data) {
  lcd.setCursor(col, row);
  lcd.print(data);
}

void displayAuthor(int col) {
  lcd.setCursor(0, col);
  lcd.print("github.com/Seweryn91");
}

