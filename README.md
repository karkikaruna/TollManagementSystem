# 🚧 Toll Management System

This project is a **Toll Management System** prototype developed during the **Mini Hackathon** organized by the **Robotics Club**.  
It demonstrates a simplified automated toll booth using embedded components and sensors.


##  Components Used

- **Keypad** – for entering vehicle or user credentials (e.g., ID or vehicle number)  
- **LCD Display (16x2)** – to show system messages, user instructions, or toll status  
- **Ultrasonic Sensor (HC-SR04)** – to detect the presence of a vehicle at the booth  
- **Servo Motor** – to simulate the opening and closing of the toll barrier  
- **Arduino Uno** – as the main microcontroller to control all the components  

## Features

- Detects vehicles using an ultrasonic sensor  
- Accepts input from users via keypad (e.g., toll ID)  
- Displays messages on an LCD screen  
- Controls servo motor to open/close barrier after validation  
- Simple and interactive toll collection prototype  

## Working Principle

1. **Vehicle Detection**:  
   The ultrasonic sensor continuously checks for the presence of a vehicle.

2. **Input Prompt**:  
   Once a vehicle is detected, the LCD prompts the driver to enter a toll ID using the keypad.

3. **Validation**:  
   After entering the ID, the system validates it (in this prototype, it's basic ID matching).

4. **Gate Operation**:  
   If valid, the servo motor rotates to open the gate; otherwise, access is denied.

5. **Display Updates**:  
   The LCD shows appropriate messages like "Enter ID", "Access Granted", or "Invalid ID".

## Team Members
- Karuna Karki
- Niraj Bista  
- Abhisek Niraula  
- Pritam Acharya  

## Recognition

We became the **First Runner-Up** at the **Mini Hackathon** organized by the **Robotics Club** by showcasing this project.

