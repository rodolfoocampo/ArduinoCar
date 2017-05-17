#include <ros.h>
#include <std_msgs/String.h>
#include <Servo.h>


/////////// Sonar ///////


Servo servo; 

int b1 = 8;
int b2 = 7;

long anVolt, inches, cm;

int sum = 0; //

int avgrange = 20; //

int freq;

ros::NodeHandle nh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);



void setup() {

  /////////////////////////////////// SERVO

  servo.attach(9);
  servo.write(0);

  /////////////////////////////////// BRUSHLESS

  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);

  ///////////////////////////////////////
  
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
 
/////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// SONAR ///////////////////////////////////////////////////////////
  for (int i = 0; i < avgrange ; i++)

  {
    anVolt = analogRead(A0) / 2;
    sum += anVolt;
    delay(1);
  }



  
  inches = sum / avgrange;
  
  cm = inches * 2.54;

  Serial.print(cm);

  Serial.print("cm");

  Serial.println();

  sum = 0;

  delay(1);

  //////////////////////////////////////////////////////////////////////////////////////////////////////////






  ///////////////////////////////////       MOTORES //////////////////////////////////////////////////////////////////////////77


  ///// 1.- SERVO

  servo.write(90);
  delay(1000);
  servo.write(180);
  delay(1000);
  servo.write(90);
  delay(1000);
  servo.write(180);


  ///// 2.- Brushless

  digitalWrite(b1, HIGH);
  digitalWrite(b2, LOW);

}
