
//// ROS libraries and variables

#include <ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle  nh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[13] = "hello mundo!";


#include <Servo.h>
/////////// Sonar ///////


Servo servo; 

int b1 = 8;
int b2 = 7;

long anVolt, inches, cm;

int sum = 0; //

int avgrange = 20; //

int freq;

void setup() {

  //// ROS node

  nh.initNode();
  nh.advertise(chatter);

  /////////////////////////////////// SERVO

  servo.attach(9);
  servo.write(0);

  /////////////////////////////////// BRUSHLESS

  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);

  ///////////////////////////////////////
 
}

void loop() {
 
////////////////////////////////////    ROS    //////////////////////////////////////////////////////////////////

  str_msg.data = hello;
  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(1000);

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
