#include <TinyGPS++.h>
#include <SoftwareSerial.h>
SoftwareSerial GPS_SoftSerial(0, 1);/* (Rx, Tx) */
TinyGPSPlus gps;      
int i=0;
volatile float minutes, seconds;
volatile int degree, secs, mins;

void setup() {
  Serial.begin(9600); 
  GPS_SoftSerial.begin(9600); 
}

void loop() {
  if(i<2)
  {
        smartDelay(1000); /* Generate precise delay of 1ms */
        unsigned long start;
        double lat_val, lng_val;
        uint8_t hr_val, min_val, sec_val;
        bool loc_valid, time_valid;
        lat_val = gps.location.lat(); /* Get latitude data */
        loc_valid = gps.location.isValid(); /* Check if valid location data is available */
        lng_val = gps.location.lng(); /* Get longtitude data */
     
        time_valid = gps.time.isValid(); 
        if(i==1)
        {/* Check if valid time data is available */
        if (!loc_valid)
        {          
          Serial.print("Latitude : ");
          Serial.println("*****");
          Serial.print("Longitude : ");
          Serial.println("*****");
        }
        else
        {
          DegMinSec(lat_val);
          Serial.print("Latitude: ");
          Serial.println(lat_val, 6);
         
          DegMinSec(lng_val); 
          Serial.print("Longitude : ");
          Serial.println(lng_val, 6);
          Serial.println("\n");
        }
   
        }
        i++;
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
