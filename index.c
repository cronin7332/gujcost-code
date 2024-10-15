// Define motor control pins for mecanum wheels
int M1_e = 8;  // Enable pin for motor 1
int M1_1 = 10;  // Motor 1 control pin 1
int M1_2 = 9;  // Motor 1 control pin 2

int M2_e = 6;  // Enable pin for motor 2
int M2_1 = 4;  // Motor 2 control pin 1
int M2_2= 5;  // Motor 2 control pin 2

int M3_e = 13;  // Enable pin for motor 3
int M3_1= 12; // Motor 3 control pin 1
int M3_2= 11; // Motor 3 control pin 2

int M4_e= 1; // Enable pin for motor 4
int M4_1= 2; // Motor 4 control pin 1
int M4_2= 3; // Motor 4 control pin 2

// Define ultrasonic sensor pins
int trigPin1 = A2;
int echoPin1 = A3;

int trigPin2 = A0;
int echoPin2 = A1;

int trigPin3 = A4;
int echoPin3 = A5;

// Function to measure distance from ultrasonic sensor
long measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  
  return distance;
}

// Function to set motor movement directions
void setMotorMovement(int Motor1, int Motor2, int logic1, int logic2) {
  digitalWrite(Motor1, logic1);
  digitalWrite(Motor2, logic2);
  
  
}

// Function to set speed for all motors
void setSpeed(int speed) {
  analogWrite(M1_e, speed);
  analogWrite(M2_e, speed);
  analogWrite(M3_e, speed);
  analogWrite(M4_e, speed);
}

// Function to move forward
void moveForward() {
  setMotorMovement(M1_1, M1_2, HIGH, LOW);  // Set direction for all motors to forward
  setMotorMovement(M2_1, M2_2, HIGH, LOW);
  setMotorMovement(M3_1, M3_2, HIGH, LOW);
  setMotorMovement(M4_1, M4_2, HIGH, LOW);

}

// Function to move backward
void moveBackward() {
 setMotorMovement(M1_1, M1_2, LOW, HIGH);  // Set direction for all motors to forward
  setMotorMovement(M2_1, M2_2,LOW, HIGH);
  setMotorMovement(M3_1, M3_2,LOW,HIGH);
  setMotorMovement(M4_1, M4_2,LOW,HIGH);
}

// Function to rotate clockwise
void rotateClockwise() {
  setMotorMovement(M1_1, M1_2, HIGH, LOW);  // Set direction for all motors to forward
  setMotorMovement(M2_1, M2_2, LOW, HIGH);
  setMotorMovement(M3_1, M3_2, HIGH, LOW);
  setMotorMovement(M4_1, M4_2, LOW, HIGH);
}

// Function to rotate counterclockwise
void rotateCounterClockwise() {
  setMotorMovement(M1_1, M1_2, LOW, HIGH);  // Set direction for all motors to forward
  setMotorMovement(M2_1, M2_2,HIGH, LOW);
  setMotorMovement(M3_1, M3_2,LOW,HIGH);
  setMotorMovement(M4_1, M4_2,HIGH,LOW);
}

// Function to stop the robot
void stopRobot() {
 setMotorMovement(M1_1, M1_2, LOW, LOW);  // Set direction for all motors to forward
  setMotorMovement(M2_1, M2_2,LOW, LOW);
  setMotorMovement(M3_1, M3_2,LOW,LOW);
  setMotorMovement(M4_1, M4_2,LOW,LOW);
}

void turnRight(){
  stopRobot();
  delay(500);
  rotateClockwise();
  delay(455);
  moveForward();
  delay(500);
}
void turnLeft(){
  stopRobot();
  delay(500);
  rotateCounterClockwise();
  delay(455);
  moveForward();
  delay(500);
}
void Uturn(){
  stopRobot();
  delay(500);
  rotateCounterClockwise();
  delay(950);
  moveForward();
  delay(500);
}
void smoothForward(long distanceLeft, long distanceRight) {
  // Adjust speed based on proximity to obstacles
  if (distanceLeft < 5 && distanceRight >= 5) {
    // Adjust speeds to avoid obstacle on the left
    analogWrite(M1_e, 250);
    analogWrite(M2_e, 150);
    analogWrite(M3_e, 250);
    analogWrite(M4_e, 150);
  }
  else if (distanceRight < 5 && distanceLeft >= 5) {
    // Adjust speeds to avoid obstacle on the right
    analogWrite(M1_e, 150);
    analogWrite(M2_e, 250);
    analogWrite(M3_e, 150);
    analogWrite(M4_e, 250);
  }
  
  else {
    // Default speed if no obstacles are close
    analogWrite(M1_e, 250);
    analogWrite(M2_e, 250);
    analogWrite(M3_e, 250);
    analogWrite(M4_e, 250);
  }
  
  // Move forward after setting speed
  moveForward();
}
void setup() {
  // Motor pins as output
  pinMode(M1_e, OUTPUT);
  pinMode(M1_1, OUTPUT);
  pinMode(M1_2, OUTPUT);

  pinMode(M2_e, OUTPUT);
  pinMode(M2_1, OUTPUT);
  pinMode(M2_2, OUTPUT);

  pinMode(M3_e, OUTPUT);
  pinMode(M3_1, OUTPUT);
  pinMode(M3_2, OUTPUT);

  pinMode(M4_e, OUTPUT);
  pinMode(M4_1, OUTPUT);
  pinMode(M4_2, OUTPUT);

  // Ultrasonic sensor pins
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  Serial.begin(9600);
}

void loop() {
  // Measure distances from ultrasonic sensors
  long distanceFront = measureDistance(trigPin1, echoPin1);
  long distanceLeft = measureDistance(trigPin2, echoPin2);
  long distanceRight = measureDistance(trigPin3, echoPin3);
  
setSpeed(250);
  // Print distances for debugging
 if (distanceFront > 15 && distanceLeft > 20 && distanceRight > 20) {
    // Case: All directions are clear, move forward
    smoothForward(distanceLeft, distanceRight);
  } 
  else if (distanceFront <= 15 && distanceLeft > 20&& distanceRight > 20) {
    // Front is blocked, but there's space to move left or right
    turnLeft(); // or you might want to turn left depending on your preference
  } 
  else if (distanceLeft <= 20&& distanceRight <= 20) {
    // Both sides are blocked
    if (distanceFront <= 15) {
      // All directions are blocked, perform a U-turn
      Uturn();
    } else {
      // Move forward if there's space in front
      smoothForward(distanceLeft, distanceRight);
    }
  } 
  else if (distanceFront <= 15 && distanceLeft <= 20) {
    // Front is blocked, turn right
    turnRight();
  } 
  else if (distanceFront <= 15 && distanceRight <= 20) {
    // Front is blocked, turn left
    turnLeft();
  }
}
