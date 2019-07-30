#include <TinyGPS++.h>
#include <SoftwareSerial.h>
SoftwareSerial GPS_SoftSerial(0, 1);/* (Rx, Tx) */
TinyGPSPlus gps;      
volatile float minutes, seconds;
volatile int degree, secs, mins;

String ssid ="qwe";
String password="qwertyuiop";
SoftwareSerial esp(6,7);
String data;
String server = "192.168.43.212";// ip 
String uri = "/wifidata.php?tempc=";

int trigPin = 11;    // Trigger
int echoPin = 12;    // Echo
long duration, cm, inches;
float per, stat1, stat2;



void setup() {
  Serial.begin(9600); 
  GPS_SoftSerial.begin(9600); 
pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}


void connectWifi() {
String cmd = "AT+CWJAP=\"" +ssid+"\",\"" + password + "\"";
esp.println(cmd);

if(esp.find("OK")) {
Serial.println("Connected!");
}
else {
connectWifi();
Serial.println("Cannot connect to wifi"); }
}

void loop() {
        smartDelay(10000); /* Generate precise delay of 1ms */
        unsigned long start;
        double lat_val, lng_val;
        uint8_t hr_val, min_val, sec_val;
        bool loc_valid, time_valid;
        lat_val = gps.location.lat(); /* Get latitude data */
        loc_valid = gps.location.isValid(); /* Check if valid location data is available */
        lng_val = gps.location.lng(); /* Get longtitude data */

     
        time_valid = gps.time.isValid();  /* Check if valid time data is available */
        if (!loc_valid)
        {          
          Serial.print("Latitude : ");
          Serial.println("*****");
          Serial.print("Longitude : ");
          Serial.println("*****");
          Serial.println("\n");
        }
        else
        {
          
  esp.begin(115200);
connectWifi();
for(;;)
{
digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
 cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
  stat1 = 50-cm;
    stat2 = stat1/50;
    per = stat2 * 100;
    
  // delay(250);
 if(per>0)
 {Serial.println("Value is");
    Serial.print(per);
    Serial.print("%");
    
 break;}} 
 
  
          DegMinSec(lat_val);
          Serial.print("Latitude: ");
          Serial.println(lat_val, 6);
         
          DegMinSec(lng_val); 
          Serial.print("Longitude : ");
          Serial.println(lng_val, 6);
          Serial.println("\n");

int locc=1;int perc;
String ltr,lang;
String loc;
String des;
perc=(int)per;
des=String(perc);
loc=String(locc);
ltr = String(lat_val,6);
lang = String(lng_val,6);
httppost(ltr,lang,loc,des);
delay(1000);     
}

}
void httppost (String data,String data1,String data2,String data3) {

esp.println("AT+CIPSTART=\"TCP\",\"" + server + "\",800");//start a TCP connection.

if( esp.find("OK")) {

Serial.println("TCP connection ready");

} delay(1000);
//data3=data3+newf;

String postRequest =

"GET " + uri +data+"&tempc1="+data1+"&status="+data2+"&per="+data3+"%"+ " HTTP/1.0\r\n" +

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

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (GPS_SoftSerial.available())  /* Encode data read from GPS while data is available on serial port */
      gps.encode(GPS_SoftSerial.read());
    /* Encode basically is used to parse the string received by the GPS and to store it in a buffer so that information can be extracted from it */
  } while (millis() - start < ms);
}

void DegMinSec( double tot_val)   /* Convert data in decimal degrees into degrees minutes seconds form */
{  
  degree = (int)tot_val;
  minutes = tot_val - degree;
  seconds = 60 * minutes;
  minutes = (int)seconds;
  mins = (int)minutes;
  seconds = seconds - minutes;
  seconds = 60 * seconds;
  secs = (int)seconds;
}
