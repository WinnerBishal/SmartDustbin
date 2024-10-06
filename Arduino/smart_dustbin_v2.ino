#include <AccelStepper.h>
#include <Servo.h>

// Define Physical Dimensions of the actutator in mm
#define switch2switch_len 1000
#define total_compart_len 800
#define n_compart 4
#define box_len 100
const int compart_len = total_compart_len / n_compart;

// Define the stepper motor pin connections
#define dirPin 2
#define stepPin 3
#define enablePin 12

// Define the servo motor pin connections
#define left_servoPin 9
#define right_servoPin 10
// Define servo open and close angle
#define servo_span 75

#define left_close_angle 10
#define left_open_angle left_close_angle + servo_span

#define right_close_angle 85
#define right_open_angle right_close_angle - servo_span 


// Define the limit switch pin connections
#define limitLeftPin 7
#define limitRightPin 8

#define st_speed 600
#define st_accel 150

// Initialize the stepper motor and servo objects
AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);
Servo servoLeft;
Servo servoRight;

// Define the waste categories
const String categories[] = { "Organic","Plastic","Metal", "Paper" };
const int numCategories = 4;

// track total steps
int totalSteps = 5020;

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Initialize the stepper motor
  stepper.setCurrentPosition(0);
  stepper.setMaxSpeed(st_speed);
  stepper.setAcceleration(st_accel);
  stepper.setPinsInverted(false, false, true);
  stepper.enableOutputs();

  // Initialize the servo motors
  servoLeft.attach(left_servoPin);
  servoRight.attach(right_servoPin);
  close_door();

  // Set the limit switches as inputs
  pinMode(limitLeftPin, INPUT_PULLUP);
  pinMode(limitRightPin, INPUT_PULLUP);

  // Calibrate the system, if not already at leftmost position
  // calibrate();
}

// void loop() {
//   static bool waitingMsgPrinted = false;

//   if (Serial.available() > 0) {
//     String wasteCategory = Serial.readStringUntil('\n');
//     Serial.println("Recieved : ");
//     Serial.println(wasteCategory);
//     for (int i = 0; i < numCategories; i++) {
//       if (wasteCategory == categories[i]) {
//         Serial.println("Recognized Waste :");
//         Serial.println(wasteCategory);
//         move_to_compart(i);
//         waitingMsgPrinted = false;
//         break;
//       }
//     }
//   } else if (!waitingMsgPrinted) {
//     Serial.println("WAITING FOR SIGNAL");
//     waitingMsgPrinted = true;
//   }
// }

void loop() {
  static bool waitingMsgPrinted = false;

  if (Serial.available() > 0) {
    String wasteCategory = Serial.readStringUntil('\n');
    Serial.println("Recieved : ");
    Serial.println(wasteCategory);
    for (int i = 0; i < numCategories; i++) {
      if (wasteCategory == categories[i]) {
        Serial.println("Recognized Waste :");
        Serial.println(wasteCategory);
        move_to_compart(i);
        waitingMsgPrinted = false;
        break;
      }
    }
  } else if (!waitingMsgPrinted) {
    Serial.println("WAITING FOR SIGNAL");
    waitingMsgPrinted = true;
  }
}

void move_to_compart(int i) {
  // Calculate all lengths required
  float stepPerLength = totalSteps / switch2switch_len;
  float switch_compart_offset = (switch2switch_len - total_compart_len) / 2;
  float compart_box_offset = (compart_len - box_len) / 2;
  float total_offset = switch_compart_offset + compart_box_offset;

  int step2compart = (total_offset * stepPerLength) + (i * compart_len * stepPerLength);
  Serial.println("Moving to Compartment ");
  /*
  Serial.println(i + 1);
  Serial.println("Steps to move : ");
  Serial.println(step2compart);
  Serial.println("Distance to move: ");
  Serial.println(step2compart / stepPerLength);
  */
  stepper.moveTo(step2compart);
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }
  delay(1000);
  /*
  Serial.println("Current Position : ");
  Serial.println(stepper.currentPosition());
  */
  Serial.println("Opening Flaps");
  open_door();
  delay(2000);
  Serial.println("Closing Flaps");
  close_door();
  delay(2000);

  Serial.println("Moving to initial position.");

  stepper.moveTo(0);
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }

  // Serial.println("Current position : ");
  // Serial.print(stepper.currentPosition());
}

void open_door(){
  servoLeft.write(left_open_angle);
  servoRight.write(right_open_angle);
}

void close_door(){
  servoLeft.write(left_close_angle);
  servoRight.write(right_close_angle);
}


/*
void calibrate() {
  if (digitalRead(limitLeftPin) == HIGH) {
    const int calibrationSpeed = st_speed;  // adjusted as experimented

    // Step 1: Move forward until right limit switch is hit
    Serial.println("CALIBRATING SPAN");
    Serial.println("Moving Out...");

    while (digitalRead(limitRightPin) == HIGH) {
      stepper.setSpeed(calibrationSpeed);
      stepper.runSpeed();
    }
    Serial.println("Reached the end.");
    delay(1000);

    stepper.setCurrentPosition(0);
    stepper.setMaxSpeed(st_speed);
    stepper.setAcceleration(st_accel);

    // Step 2: Move backward until left limit switch is hit
    Serial.println("Returning....");
    while (digitalRead(limitLeftPin) == HIGH) {
      stepper.setSpeed(-calibrationSpeed);
      stepper.runSpeed();
    }

    totalSteps = abs(stepper.currentPosition());
    stepper.setCurrentPosition(0);
    stepper.setMaxSpeed(st_speed);
    stepper.setAcceleration(st_accel);

    Serial.print("Span Calibration completed. Current Position : ");
    Serial.println(stepper.currentPosition());
    Serial.println("Total steps : ");
    Serial.println(totalSteps);
    Serial.println("Steps per mm : ");
    Serial.println(totalSteps / switch2switch_len);
  } else {
    stepper.setCurrentPosition(0);
    stepper.setMaxSpeed(st_speed);
    stepper.setAcceleration(st_accel);

    Serial.println("CALIBRATION CANCELLED. Already at initial position.");
    Serial.println("Current Position:");
    Serial.println(stepper.currentPosition());
  }
}
*/
