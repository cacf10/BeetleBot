/***********************************************************
File name: BeetleBot.ino
Description: Robot motion can be controlled through mobile APP or Python GUI. 
Date: 2025/12/29
***********************************************************/
#include "hexpod.h"

#include <SoftwareSerial.h>

SoftwareSerial softwareSerial1(A0, A1);

String text1 = "1";
String text2 = "2";
String text3 = "3";
String text4 = "4";
String text5 = "5";
String text6 = "10";
String text7 = "7";
String text8 = "8";
String text9 = "9";

String comdata = "";
char judge;
QUANRUPED q;
void ESP8266_ATCOMMAND(){
   Serial.begin(115200);       // set up a wifi serial communication baud rate 115200
//   pinMode(controller, OUTPUT);    // sets the RelayPin to be an output
  //  Serial.println("AT+CWMODE=3\r\n");//set to softAP+station mode
  //  delay(2000);     //delay 4s
   
  //  Serial.println("AT+CWSAP=\"BeetleBot\",\"12345678\",8,2\r\n");   //TCP Protocol, server IP addr, port
  //   delay(2000);     //delay 4s
  //  Serial.println("AT+RST\r\n");     //reset wifi
  //  delay(2000);     //delay 4s
  
  //  Serial.println("AT+CIPMUX=1\r\n");
  //  delay(2000);
  //  Serial.println("AT+CIPSERVER=1\r\n");
  //  delay(2000);
  //  Serial.println("AT+CIPSTO=7000\r\n");
  //  delay(2000);
}

void setup()
{
  q.servo_attach();
  q.self_balanced_setup();
  softwareSerial1.begin(115200);       // set up a wifi serial communication baud rate 115200
  Serial.begin(9600);       // set up a wifi serial communication baud rate 115200
}
void loop()
{
  if (softwareSerial1.available()>0)
  {  
    char c = softwareSerial1.read();  
    //Serial.write(c);
    Serial.println(c, HEX);
    Serial.println("******************************************************************");
    switch(c){
      case '1': {q.moveforward();
               break;}
      case '2': {q.movebackward();
               break;}
      case '3': {q.turnright();
               break;}
      case '4': {q.turnleft();
               break; }
      case '5': {q.steaty();
               break; }
      case '6': {q.attack();
               break;}
      case '7': {q.steaty();
               break;}
      case '8': {q.advoid();
               break;}
      default:  {Serial.println("No Match");
                break;}
  }
  }
}

