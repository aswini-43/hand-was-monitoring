#include<SoftwareSerial.h>
SoftwareSerial mySerial(10,11);

void open1();
void open2();
void san();

int water=12;
int sanitizer1=11;  
int sanitizer2=10;

int soap1=9;
int soap2=8;


const int trig=2;
const int echo=3;

float duration, distance;

//int blow=5;


void setup() {
mySerial.begin(9600);
pinMode(water, OUTPUT);
pinMode(sanitizer1, OUTPUT);
pinMode(soap1, OUTPUT);
pinMode(sanitizer2, OUTPUT);
pinMode(soap2, OUTPUT);
pinMode(trig, OUTPUT);
pinMode(echo, INPUT);

Serial.begin(9600);

//pinMode(blow, OUTPUT);


}


void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = (duration*0.0343)/2;
   
  Serial.print(distance);
  Serial.println("cm");
  delay(100);

 
  if(distance<=20 && distance!=0 )  
  {
   open1();  
   delay(5000);
   open2();
   delay(2000);
    san();
    delay(2000);
   
  }

  else
  {
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
  }


//String sensor_data ="a"+String(distance)+"b"+"c"+String(distance2)+"L";
//mySerial.print(sensor_data);
//Serial.println(sensor_data);
 
}
  void open1()
  {
    int distance=100;
    String sensor_data ="a"+String(distance)+"b";
    mySerial.print(sensor_data);
    Serial.println(sensor_data);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
   
    digitalWrite(water, HIGH);
    delay(5000);
    digitalWrite(water, LOW);
    delay(1000);    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    distance=010;
    sensor_data ="a"+String(distance)+"b";
    mySerial.print(sensor_data);
    Serial.println(sensor_data);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
    digitalWrite(soap1, HIGH);
    digitalWrite(soap2, LOW);
    delay(1000);  
    digitalWrite(soap1, LOW);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    distance=100;
    sensor_data ="a"+String(distance)+"b";
    mySerial.print(sensor_data);
    Serial.println(sensor_data);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  }
  void open2()
  {
    digitalWrite(water, HIGH);
    delay(8000);
    digitalWrite(water, LOW);    
  }
  void san()
  {
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int distance=001;
    String sensor_data ="a"+String(distance)+"b";
    mySerial.print(sensor_data);
    Serial.println(sensor_data);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      digitalWrite(sanitizer1, HIGH);
      digitalWrite(sanitizer2, LOW);
    delay(1000);
    digitalWrite(sanitizer1, LOW);
  }