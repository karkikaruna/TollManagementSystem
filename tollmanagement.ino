#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

char key_pressed;
String inputPassword;
String tollAmount = "25"; 

const byte number_of_rows = 4;
const byte number_of_columns = 4;

byte row_pins[number_of_rows] = {2, 3, 4, 5}; 
byte column_pins[number_of_columns] = {6, 7, 8, 9}; 

char key_array[number_of_rows][number_of_columns] = {  
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

Keypad k = Keypad(makeKeymap(key_array), row_pins, column_pins, number_of_rows, number_of_columns);

int trigPin = 10; 
int echoPin = 11;
int led_pin=A5;
long duration;
int distance;

Servo servoMotor;

LiquidCrystal lcd_1(13, 12, A1, A2, A3, A4);

enum GateState { GATE_OFF, CAR_DETECTED, WAIT_FOR_CONFIRMATION, ENTER_TOLL, GATE_OPEN };
GateState currentState = GATE_OFF;

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    servoMotor.attach(A0); 
  	pinMode(led_pin,OUTPUT);
  	digitalWrite(led_pin,LOW);

    lcd_1.begin(16, 2);
    lcd_1.setCursor(0, 0);
    lcd_1.print("GATE:OFF");
  
    Serial.begin(9600);
    closeGate(); 
}

int calculateDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    return distance;  
}

void openGate() {
    servoMotor.write(90);
    Serial.println("Gate opened");
}

void closeGate() {
    servoMotor.write(0); 
    Serial.println("Gate closed");
}

void inputTollFunction() {
    key_pressed = k.getKey();
    if (key_pressed) {
        lcd_1.setCursor(5 + inputPassword.length(), 1);
        lcd_1.print(key_pressed);
        inputPassword += key_pressed;
        
        if (key_pressed == 'C') {
            lcd_1.setCursor(0, 1);
            lcd_1.print("$               ");
            inputPassword = "";
        }

        if (inputPassword == tollAmount) {
            lcd_1.clear();
            lcd_1.print("Correct");
            delay(1000); 
            lcd_1.setCursor(0, 0);
            lcd_1.print("GATE:OPEN");
            openGate();
            currentState = GATE_OPEN;
        } else if (key_pressed == '#') {
            lcd_1.setCursor(0, 1);
            lcd_1.print("Incorrect Toll ");
            delay(1000);
            lcd_1.clear();
            lcd_1.setCursor(0, 0);
            lcd_1.print("Enter Toll:");
            lcd_1.setCursor(0, 1);
            lcd_1.print("$");
            inputPassword = "";
        }
    }
}

void gateInput() {
    key_pressed = k.getKey();
    if (key_pressed == 'A') {
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Enter Toll:");
        lcd_1.setCursor(0, 1);
        lcd_1.print("$");
        inputPassword = "";
        currentState = ENTER_TOLL;
    }
}

void loop() {
    distance = calculateDistance();
    Serial.println("Distance: " + String(distance));
    
    switch (currentState) {
        case GATE_OFF:
            if (distance < 20) {
                digitalWrite(led_pin,HIGH);
              	lcd_1.setCursor(0, 0);
                lcd_1.print("Car Detected   ");
                delay(100);
                lcd_1.setCursor(0, 1);
                lcd_1.print("TOLL: $" + tollAmount);
                delay(300);
                lcd_1.clear();
                lcd_1.print("Press A");
                currentState = WAIT_FOR_CONFIRMATION;
                Serial.println("Car detected, waiting for confirmation");
            }
            break;

        case WAIT_FOR_CONFIRMATION:
            gateInput();
            break;

        case ENTER_TOLL:
            inputTollFunction();
            break;

        case GATE_OPEN:
            if (distance >= 20) {
              	digitalWrite(led_pin,LOW);
                lcd_1.clear();
                lcd_1.setCursor(0, 0);
                lcd_1.print("GATE:OFF");
                closeGate();
                currentState = GATE_OFF;
            }
      		else GATE_OPEN;
            break;
    }
}