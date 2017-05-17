#include <Servo.h>
/////////// Sonar ///////


Servo servo;


//// ROS libraries and variables

#include <ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle  nh;
geometry_msgs::Twist sens_msg;
geometry_msgs::Twist rec_msg;
ros::Publisher chatter("chatter", &sens_msg);

int distance;
int b1 = 8;
int b2 = 7;

void messageCb(const geometry_msgs::Twist& toggle_msg){
  distance = (int)toggle_msg.linear.x;
    if (distance > 30){
      digitalWrite(b1, HIGH);
      digitalWrite(b2, LOW);
  } else {
      digitalWrite(b1, LOW);
      digitalWrite(b2, LOW);
  }
}



ros::Subscriber<geometry_msgs::Twist> sub("chatter", &messageCb );



long anVolt, inches, cm;

int sum = 0; //

int avgrange = 20; //

int freq;

void setup() {

  //// ROS node

  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);

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

  // publicar distancia
  sens_msg.linear.x = cm;
  sens_msg.linear.y = distance;
  chatter.publish( &sens_msg );
  nh.spinOnce();
  delay(20);

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




}
