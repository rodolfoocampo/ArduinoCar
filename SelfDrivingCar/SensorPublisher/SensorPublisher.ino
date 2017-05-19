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
geometry_msgs::Twist lords_command;
const int pwPin = 6;
long pulse;

// cambiar el topico a "sensor"
ros::Publisher sensor("sensor", &sens_msg);

int distance;
int b1 = 8;
int b2 = 7;
long peso;

/// FOTO

long luz;

void messageCb(const geometry_msgs::Twist& toggle_msg){
  lords_command = toggle_msg;
}

ros::Subscriber<geometry_msgs::Twist> sub("motors", &messageCb );

long anVolt, inches, cm;

int sum = 0; //

int avgrange = 20; //

int freq;

void setup() {

  //// ROS node

  nh.initNode();
  nh.advertise(sensor);
  nh.subscribe(sub);
  

  /////////////////////////////////// SERVO

  servo.attach(9);

  /////////////////////////////////// DC

  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  
  /////////////////////////////////////// GALGA

  pinMode(A12,INPUT);

  /////////////////////////////////////// FOTORRESISTENCIA

  pinMode(A7,INPUT);

  ////////// LUZ

  pinMode(50, OUTPUT);
  
}

void loop() {

/////// FOTORRESISTENCIA Y LUZ

luz = analogRead(A7);
 
////////////////////////////////////    ROS    //////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// SONAR ///////////////////////////////////////////////////////////
 /* for (int i = 0; i < avgrange ; i++)

  {
    anVolt = analogRead(A0) / 2;
    sum += anVolt;
    delay(100);
  }
*/

  pulse = pulseIn(pwPin, HIGH);
  inches = pulse / 147; 
  cm = inches * 2.54 + 4;

  // Obtener distancia
  sens_msg.linear.x = cm;

  // Obtener peso

  peso = analogRead(A12);
  
  sens_msg.linear.y = peso;

  // Obtener luz

  sens_msg.linear.z = luz;

  if(sens_msg.linear.z < 2){
  digitalWrite(50, HIGH);
 } else {
  digitalWrite(50, LOW);
  }
  
  sensor.publish(&sens_msg);
  nh.spinOnce();
  delay(20);

  cm = 0;
  sum = 0;

  //////////////////////////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////       MOTORES //////////////////////////////////////////////////////////////////////////77


  ///// 1.- SERVO
  servo.write(90);
  ///// 2.- Motor


  if (lords_command.linear.x == -1){
      digitalWrite(b1, LOW);
      digitalWrite(b2, HIGH);
  } else if (lords_command.linear.x == 1) {
      digitalWrite(b1, HIGH);
      digitalWrite(b2, LOW);
      if (lords_command.linear.y == 2) {
         servo.write(180);
      }
  } else if (lords_command.linear.x == 0) {
      digitalWrite(b1, LOW);
      digitalWrite(b2, LOW);
  } 

  delay(500);

}
