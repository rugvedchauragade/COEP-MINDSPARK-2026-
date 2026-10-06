// ================= MOTOR DRIVER =================

// MOTOR 1
#define SLEEP1 25
#define DIR1   26
#define PWM1   27

// MOTOR 2
#define PWM2   14
#define DIR2   33
#define SLEEP2 32


// ================= RC RECEIVER =================

#define CH1 18   // LEFT / RIGHT
#define CH2 19   // FORWARD / BACKWARD


// ================= SETTINGS =================

int maxSpeed = 200;

// How quickly the motors accelerate/decelerate
int acceleration = 15;


// Current motor speeds
int currentLeft  = 0;
int currentRight = 0;


// ================= STOP =================

void stopMotors() {
  analogWrite(PWM1, 0);
  analogWrite(PWM2, 0);
}


// ================= MOTOR CONTROL =================

void setMotor1(int speed) {

  if (speed > 0) {
    // MOTOR 1 FORWARD
    digitalWrite(DIR1, LOW);
    analogWrite(PWM1, speed);
  }

  else if (speed < 0) {
    // MOTOR 1 BACKWARD
    digitalWrite(DIR1, HIGH);
    analogWrite(PWM1, -speed);
  }

  else {
    analogWrite(PWM1, 0);
  }
}


void setMotor2(int speed) {

  if (speed > 0) {
    // MOTOR 2 FORWARD
    digitalWrite(DIR2, HIGH);
    analogWrite(PWM2, speed);
  }

  else if (speed < 0) {
    // MOTOR 2 BACKWARD
    digitalWrite(DIR2, LOW);
    analogWrite(PWM2, -speed);
  }

  else {
    analogWrite(PWM2, 0);
  }
}


// ================= SMOOTHING =================

int smoothSpeed(int current, int target) {

  if (current < target) {
    current += acceleration;

    if (current > target)
      current = target;
  }

  else if (current > target) {
    current -= acceleration;

    if (current < target)
      current = target;
  }

  return current;
}


// ================= SETUP =================

void setup() {

  Serial.begin(115200);

  pinMode(SLEEP1, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(PWM1, OUTPUT);

  pinMode(SLEEP2, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(PWM2, OUTPUT);

  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);

  // Enable motors
  digitalWrite(SLEEP1, LOW);
  digitalWrite(SLEEP2, LOW);

  stopMotors();

  Serial.println("================================");
  Serial.println("SMOOTH RC ROBOT STARTED");
  Serial.println("================================");

  delay(1000);
}


// ================= LOOP =================

void loop() {

  // Read receiver
  unsigned long ch1 = pulseIn(CH1, HIGH, 25000);
  unsigned long ch2 = pulseIn(CH2, HIGH, 25000);


  // ================= FAILSAFE =================

  if (ch1 < 900 || ch1 > 2100 ||
      ch2 < 900 || ch2 > 2100) {

    // Slowly stop instead of suddenly stopping
    currentLeft = smoothSpeed(currentLeft, 0);
    currentRight = smoothSpeed(currentRight, 0);

    setMotor1(currentLeft);
    setMotor2(currentRight);

    delay(10);
    return;
  }


  // ================= READ STICKS =================

  int throttle = (int)ch2 - 1500;
  int steering = (int)ch1 - 1500;


  // Deadzone
  if (abs(throttle) < 70)
    throttle = 0;

  if (abs(steering) < 70)
    steering = 0;


  // ================= MIXING =================

  int targetLeft =
    map(throttle + steering,
        -1000, 1000,
        -maxSpeed, maxSpeed);

  int targetRight =
    map(throttle - steering,
        -1000, 1000,
        -maxSpeed, maxSpeed);


  targetLeft = constrain(targetLeft, -maxSpeed, maxSpeed);
  targetRight = constrain(targetRight, -maxSpeed, maxSpeed);


  // ================= SMOOTH ACCELERATION =================

  currentLeft =
    smoothSpeed(currentLeft, targetLeft);

  currentRight =
    smoothSpeed(currentRight, targetRight);


  // ================= DRIVE MOTORS =================

  setMotor1(currentLeft);
  setMotor2(currentRight);


  // ================= DEBUG =================

  Serial.print("CH1: ");
  Serial.print(ch1);

  Serial.print("  CH2: ");
  Serial.print(ch2);

  Serial.print("  L: ");
  Serial.print(currentLeft);

  Serial.print("  R: ");
  Serial.println(currentRight);


  delay(10);
}