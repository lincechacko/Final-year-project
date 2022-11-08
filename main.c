#include <TinyGPS.h>
#include <Wire.h>
#include<SoftwareSerial.h>


#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#define flame 2
#define vib A0
#define echoPin 3
#define trigPin 4

SoftwareSerial mySerial(6,7);//gsm pins
long duration;
int distance1,distance2;
/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);


void displaySensorDetails(void)
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}



void displayDataRate(void)
{
  Serial.print  ("Data Rate:    ");
 
  switch(accel.getDataRate())
  {
    case ADXL345_DATARATE_3200_HZ:
      Serial.print  ("3200 ");
      break;
    case ADXL345_DATARATE_1600_HZ:
      Serial.print  ("1600 ");
      break;
    case ADXL345_DATARATE_800_HZ:
      Serial.print  ("800 ");
      break;
    case ADXL345_DATARATE_400_HZ:
      Serial.print  ("400 ");
      break;
    case ADXL345_DATARATE_200_HZ:
      Serial.print  ("200 ");
      break;
    case ADXL345_DATARATE_100_HZ:
      Serial.print  ("100 ");
      break;
    case ADXL345_DATARATE_50_HZ:
      Serial.print  ("50 ");
      break;
    case ADXL345_DATARATE_25_HZ:
      Serial.print  ("25 ");
      break;
    case ADXL345_DATARATE_12_5_HZ:
      Serial.print  ("12.5 ");
      break;
    case ADXL345_DATARATE_6_25HZ:
      Serial.print  ("6.25 ");
      break;
    case ADXL345_DATARATE_3_13_HZ:
      Serial.print  ("3.13 ");
      break;
    case ADXL345_DATARATE_1_56_HZ:
      Serial.print  ("1.56 ");
      break;
    case ADXL345_DATARATE_0_78_HZ:
      Serial.print  ("0.78 ");
      break;
    case ADXL345_DATARATE_0_39_HZ:
      Serial.print  ("0.39 ");
      break;
    case ADXL345_DATARATE_0_20_HZ:
      Serial.print  ("0.20 ");
      break;
    case ADXL345_DATARATE_0_10_HZ:
      Serial.print  ("0.10 ");
      break;
    default:
      Serial.print  ("???? ");
      break;
  }  
  Serial.println(" Hz");  
}

void displayRange(void)
{
  Serial.print  ("Range:         +/- ");
 
  switch(accel.getRange())
  {
    case ADXL345_RANGE_16_G:
      Serial.print  ("16 ");
      break;
    case ADXL345_RANGE_8_G:
      Serial.print  ("8 ");
      break;
    case ADXL345_RANGE_4_G:
      Serial.print  ("4 ");
      break;
    case ADXL345_RANGE_2_G:
      Serial.print  ("2 ");
      break;
    default:
      Serial.print  ("?? ");
      break;
  }  
  Serial.println(" g");  
}
int ultrasound1()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance1 = duration * 0.034 / 2;
//  Serial.print("Distance: ");
 // Serial.print(distance);
 // Serial.println(" cm");
  return(distance1);
}

int ultrasound2()
{
  digitalWrite(12, LOW);
  delayMicroseconds(2);
  digitalWrite(12, HIGH);
  delayMicroseconds(10);
  digitalWrite(12, LOW);
  duration = pulseIn(13, HIGH);
  distance2 = duration * 0.034 / 2;
//  Serial.print("Distance: ");
 // Serial.print(distance);
 // Serial.println(" cm");
  return(distance2);
}


void setup(void)
{ int mode;
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(19,OUTPUT);
  pinMode(18,OUTPUT);
  pinMode(48,INPUT);
 // pinMode(49,INPUT);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(18,HIGH);
  digitalWrite(48,HIGH);
  digitalWrite(49,HIGH);
  mySerial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(12, OUTPUT);
  pinMode(13, INPUT);
 
  Serial.println("systen is intializing..");
 
#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif
  Serial.begin(9600);
  Serial.println("Accelerometer Test"); Serial.println("");
 
  /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }

  /* Set the range to whatever is appropriate for your project */
  accel.setRange(ADXL345_RANGE_16_G);
  // accel.setRange(ADXL345_RANGE_8_G);
  // accel.setRange(ADXL345_RANGE_4_G);
  // accel.setRange(ADXL345_RANGE_2_G);
 
  /* Display some basic information on this sensor */
  displaySensorDetails();
 
  /* Display additional settings (outside the scope of sensor_t) */
  displayDataRate();
  displayRange();
  Serial.println("");
}
int mode;

void loop(void)
{ sms:
  int vibval,flameval,dist,dist1;
  /* Get a new sensor event */
  sensors_event_t event;
  accel.getEvent(&event);
 
  /* Display the results (acceleration is measured in m/s^2) */
  vibval=analogRead(vib);
  flameval=digitalRead(flame);
  dist=ultrasound1();
  dist1=ultrasound2();
 if(dist<50 || dist1<50)
  {
    digitalWrite(19,HIGH);
    delay(75);
    digitalWrite(19,LOW);
    delay(75);
  }

 if((event.acceleration.x)>9 || (event.acceleration.x)<-9 || (event.acceleration.y)>9 || (event.acceleration.y)<-9 || vibval >1000 || flameval==1)
 
 {
 
 
  for(int i=0;i<10;i++)
  {
    mode=digitalRead(48);
    if(mode==LOW)
    {
      goto sms;
    }
    delay(1000);
    Serial.println("mode::");
    Serial.print(mode);
  }
 
 /*  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
  delay(500);
 
*/
 mySerial.println("AT+CMGF=1");    
     delay(1000);  
     mySerial.println("AT+CMGS=\"+918281382590\"\r");
     delay(1000);
     mySerial.println("Accident Detected!!!");
     delay(100);
     mySerial.println("http://www.google.com/maps/place/9.317726077067888,76.6178343970515");                                                                          
     mySerial.println((char)26);
     delay(1000);
 if (mySerial.available()>0)
   Serial.write(mySerial.read());
 
 
//  Serial.println(vibval);
//  Serial.println(flameval);
 }
 
}
