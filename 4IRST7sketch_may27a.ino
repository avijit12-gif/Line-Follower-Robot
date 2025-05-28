// IR Sensor pins
#define L2 A0
#define L1 11
#define R1 12
#define R2 A1

#define BLACK HIGH
#define WHITE LOW

// Motor driver pins
int enableRightMotor = 6;
int rightMotorPin1 = 7;
int rightMotorPin2 = 8;

int enableLeftMotor = 5;
int leftMotorPin1 = 9;
int leftMotorPin2 = 10;

// Speeds
int BASE_SPEED = 80;
int SLIGHT_TURN_SPEED = 65;
int TURN_SPEED = 55;
int HARD_TURN_SPEED = 50;

String lastTurn = "STRAIGHT";

void setup() {
  Serial.begin(9600);
  
  pinMode(L2, INPUT);
  pinMode(L1, INPUT);
  pinMode(R1, INPUT);
  pinMode(R2, INPUT);

  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  rotateMotor(0, 0); // Stop at start
}

void loop() {
  int valL2 = digitalRead(L2);
  int valL1 = digitalRead(L1);
  int valR1 = digitalRead(R1);
  int valR2 = digitalRead(R2);

  Serial.print("L2: "); Serial.print(valL2);
  Serial.print(" | L1: "); Serial.print(valL1);
  Serial.print(" | R1: "); Serial.print(valR1);
  Serial.print(" | R2: "); Serial.println(valR2);

  // Line completely lost
  if (valL2 == WHITE && valL1 == WHITE && valR1 == WHITE && valR2 == WHITE) {
    if (lastTurn == "LEFT") {
      rotateMotor(TURN_SPEED, -TURN_SPEED); // Try left
    } else if (lastTurn == "RIGHT") {
      rotateMotor(-TURN_SPEED, TURN_SPEED); // Try right
    } else {
      rotateMotor(0, 0);
    }
    delay(150);
    return;
  }

  // Centered on line
  if ((valL1 == BLACK && valR1 == BLACK) || (valL1 == BLACK || valR1 == BLACK)) {
    rotateMotor(BASE_SPEED, BASE_SPEED);
    lastTurn = "STRAIGHT";
  }
  // Slight left if L2 sees black
  else if (valL2 == BLACK) {
    rotateMotor(SLIGHT_TURN_SPEED, BASE_SPEED);
    lastTurn = "LEFT";

    // Keep turning left until re-centered
    while (digitalRead(L1) == WHITE && digitalRead(R1) == WHITE) {
      rotateMotor(SLIGHT_TURN_SPEED, BASE_SPEED);
      delay(5);
    }
  }
  // Slight right if R2 sees black
  else if (valR2 == BLACK) {
    rotateMotor(BASE_SPEED, SLIGHT_TURN_SPEED);
    lastTurn = "RIGHT";

    // Keep turning right until re-centered
    while (digitalRead(L1) == WHITE && digitalRead(R1) == WHITE) {
      rotateMotor(BASE_SPEED, SLIGHT_TURN_SPEED);
      delay(5);
    }
  }
  else {
    rotateMotor(0, 0); // Just in case
  }

  delay(5); // Slight delay to stabilize sensor reads
}

void rotateMotor(int leftMotorSpeed, int rightMotorSpeed) {
  // LEFT motor direction
  if (leftMotorSpeed > 0) {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  } else if (leftMotorSpeed < 0) {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  } else {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
  }

  // RIGHT motor direction
  if (rightMotorSpeed > 0) {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  } else if (rightMotorSpeed < 0) {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  } else {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
  }

  analogWrite(enableLeftMotor, constrain(abs(leftMotorSpeed), 0, 255));
  analogWrite(enableRightMotor, constrain(abs(rightMotorSpeed), 0, 255));
}
