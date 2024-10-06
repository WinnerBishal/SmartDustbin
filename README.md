# Smart Waste Segregation System

## Overview

This project focuses on developing a **Smart Dustbin** system that integrates **AI and IoT** technologies to detect and segregate waste automatically into different categories. The system utilizes **YOLO v7** for waste detection and segregation, combined with an actuator system for efficient waste disposal.

### Key Features:
- **Automated waste detection and segregation** using YOLO v7.
- **Actuator-driven smart dustbin** that opens and closes based on waste type.
- **Waste type classification** into categories such as plastics, metals, paper, etc.
- **Efficient and sustainable waste management**.

---

## Motivation

The need for smart waste management systems arises from the increasing public waste disposal challenges and the necessity for a cleaner and more sustainable environment. Our system provides a solution that automates waste segregation, improving hygiene, and reducing contamination.

---

## Project Components

### 1. **AI Detection System**
   - Utilizes YOLO v7 to detect waste types.
   - Categorizes waste into pre-defined classes.
   

### 2. **Actuator System**
   - Driven by stepper motors and controlled by an Arduino Mega.
   - Mechanism involves precise linear motion using belts and pulleys.
   - Servo motors operate flaps for waste disposal.
   
   ![image](https://github.com/user-attachments/assets/24137e9b-61b0-4833-ad15-34d69c6295fa)
   ![image](https://github.com/user-attachments/assets/b8fc4aa1-fa6b-498c-9dba-a8e01337e8b4)


### 3. **Hardware Components**
   - **Arduino Mega**: Main microcontroller for controlling the actuator system.
   - **Stepper Motors**: Control the waste carrier's movement between compartments.
   - **Servo Motors**: Operate flaps for selective disposal.
   - **A4988 Driver**: Controls stepper motor movements.
   - **Limit Switches**: Ensure proper positioning of the waste carrier.
     
---

## System Design and Implementation

### Concept Design
The system design consists of a waste detection mechanism and an actuator-based disposal system. The smart dustbin segregates waste based on type and moves the carrier to the correct compartment for disposal.

- **Mechanical Design**: Modeled using **Fusion 360**.
- **Linkage Mechanism**: Simulated using **Linkage Software**.

   ![image](https://github.com/user-attachments/assets/16ad2a83-4e4a-449a-8d48-0d7795ffe827)
   ![image](https://github.com/user-attachments/assets/ddf07207-2e9c-4f5d-8771-b49896d79a5f)

### Methodology
1. **Waste Detection**: YOLO v7 model classifies the waste based on images.
2. **Control System**: Arduino receives classification data and moves the waste carrier to the respective bin.
3. **Actuation**: Servo motors open and close flaps to drop waste into the appropriate bin.

![image](https://github.com/user-attachments/assets/83654459-8d8f-45e9-a548-4cb5083382ee)


### Testing and Results
The system was tested successfully with the waste categories provided via serial input. The motion of the stepper motors and servos was observed to be smooth and accurate.

   **PROOF OF CONCEPT**
   ![image](https://github.com/user-attachments/assets/291c1836-a399-4fec-adee-bc14580ea901)



---

## Challenges and Future Improvements
- **Improving Servo Torque**: The current linkage mechanism for flap opening can be optimized for better torque.
- **System Speed**: Further calibration can enhance the speed of operation without compromising accuracy.

---

## Conclusion
This project demonstrates the successful implementation of a **Smart Waste Segregation System** that integrates AI and actuator mechanisms. The use of **YOLO v7** for waste detection and classification, combined with precise mechanical systems, creates an efficient waste management solution.

---

## Installation Instructions
1. Clone the repository: 
   ```bash
   git clone https://github.com/yourusername/SmartDustbin.git
