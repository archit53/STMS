#include "SoftwareSerial.h"
String ssid ="naman";
String password="123456788";
SoftwareSerial esp(6,7);

String data;
String server = "192.168.43.67"; // www.example.com
String uri = "/wifidata.php?tempc=";// our example is /esppost.php


void setup() {
Serial.begin(9600);
esp.begin(115200);
connectWifi();
}

void connectWifi() {
String cmd = "AT+CWJAP=\"" +ssid+"\",\"" + password + "\"";
esp.println(cmd);
delay(4000);
if(esp.find("OK")) {
Serial.println("Connected!");
}
else {
connectWifi();
Serial.println("Cannot connect to wifi"); }
}

void loop () {
data=23;
httppost(data+"%");
delay(1000);
}

void httppost (String data) {

esp.println("AT+CIPSTART=\"TCP\",\"" + server + "\",80");//start a TCP connection.

if( esp.find("OK")) {

Serial.println("TCP connection ready");

} delay(1000);

String postRequest =

"GET " + uri +data+ " HTTP/1.0\r\n" +

"Host: " + server + "\r\n" +

"Accept: " + "/" + "\r\n" +

"Content-Length: " + data.length() + "\r\n" +

"Content-Type: application/x-www-form-urlencoded\r\n" +

"\r\n" ;

String sendCmd = "AT+CIPSEND=";//determine the number of caracters to be sent.

esp.print(sendCmd);

esp.println(postRequest.length() );

delay(500);

if(esp.find(">")) { Serial.println("Sending.."); esp.print(postRequest);

if( esp.find("SEND OK")) { Serial.println("Packet sent");

while (esp.available()) {

String tmpResp = esp.readString();

Serial.println(tmpResp);

}

// close the connection

esp.println("AT+CIPCLOSE");

}

}
}
