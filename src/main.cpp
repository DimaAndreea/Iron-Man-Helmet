#include <Arduino.h>
#include <IRremote.h>
#include <Servo.h>

// hardware pins
const int IR_PIN = 2;
const int LED_PIN_1 = 3;
const int LED_PIN_2 = 11;
const int BUZZER_PIN = 6;
const int SERVO_PIN_1 = 9;
const int SERVO_PIN_2 = 10;

// IR codes
const unsigned long BREATH_ANIMATION_CODE = 0xBA45FF00;  // breath animation
const unsigned long TOGGLE_LEDS_CODE = 0xB946FF00;       // toggle both LEDs
const unsigned long LED1_AND_BREATH_CODE = 0xB847FF00;   // LED1 on, LED2 breath
const unsigned long LED2_AND_BREATH_CODE = 0xB04FFF00;   // LED2 on, LED1 breath
const unsigned long FAST_BREATH_ANIMATION_CODE = 0xBB44FF00;  // fast breath animation
const unsigned long BUZZER_CODE = 0xBF40FF00;            // buzzer control
const unsigned long BUZZER_INTERRUPT_CODE = 0xE619FF00;  // interrupt to stop buzzer
const unsigned long SERVO_PLUS_CODE = 0xA55AFF00;        // clockwise servo rotation
const unsigned long SERVO_MINUS_CODE = 0xF708FF00;       // counter-clockwise servo rotation

// states
bool led1State = false;
bool led2State = false;
volatile bool buzzerState = false;  // volatile for use with interrupts
int servoAngle1 = 90;
int servoAngle2 = 90;  // mirror movement
bool cwRotation = false, ccwRotation = false;
bool breathAnimationState = false;
bool fastBreathAnimationState = false;
bool toggleLedsState = false;
bool led1AndBreathState = false;
bool led2AndBreathState = false;
bool led2BreathState = false;

Servo servo1, servo2;

// function to reset all LED states
void resetLeds() {
  breathAnimationState = false;
  fastBreathAnimationState = false;
  toggleLedsState = false;
  led1AndBreathState = false;
  led2AndBreathState = false;
  led2BreathState = false;

  digitalWrite(LED_PIN_1, LOW);
  digitalWrite(LED_PIN_2, LOW);

  OCR2A = 0;
  OCR2B = 0;
  TCCR2A &= ~((1 << COM2A1) | (1 << COM2B1));  // disable PWM for OC2A and OC2B
}

// interrupt service routine for buzzer
void stopBuzzerInterrupt() {
  buzzerState = false;  // set buzzer state to off
  digitalWrite(BUZZER_PIN, LOW);
  Serial.println("buzzer stopped by interrupt");
}

// handle servo motor control
void handleServoControl() {
  static unsigned long lastServoUpdateTime = 0;

  if (millis() - lastServoUpdateTime > 8) {
    lastServoUpdateTime = millis();

    if (cwRotation && servoAngle1 < 175) {
      servoAngle1 += 8;
      servoAngle2 = 180 - servoAngle1;
      servo1.write(servoAngle1);
      servo2.write(servoAngle2);
      Serial.print("servo 1 angle: ");
      Serial.print(servoAngle1);
      Serial.print(", servo 2 angle: ");
      Serial.println(servoAngle2);
    }

    if (ccwRotation && servoAngle1 > 5) {
      servoAngle1 -= 8;
      servoAngle2 = 180 - servoAngle1;
      servo1.write(servoAngle1);
      servo2.write(servoAngle2);
      Serial.print("servo 1 angle: ");
      Serial.print(servoAngle1);
      Serial.print(", servo 2 angle: ");
      Serial.println(servoAngle2);
    }
  }
}

// handle buzzer control
void handleBuzzer() {
  if (buzzerState) {
    digitalWrite(BUZZER_PIN, HIGH);
    delayMicroseconds(500);
    digitalWrite(BUZZER_PIN, LOW);
    delayMicroseconds(500);
  }
}

// breath animation for LEDs using Timer2
void handleBreathAnimation() {
  static int brightness = 0;
  static int fadeAmount = 5;
  static unsigned long lastBreathUpdate = 0;

  if (millis() - lastBreathUpdate > 30) {
    lastBreathUpdate = millis();

    brightness += fadeAmount;
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }

    OCR2A = brightness;
    OCR2B = brightness;
  }
}

// fast breath animation for LEDs using Timer2
void handleFastBreathAnimation() {
  static int brightness = 0;
  static int fadeAmount = 10;
  static unsigned long lastFastBreathUpdate = 0;

  if (millis() - lastFastBreathUpdate > 15) {
    lastFastBreathUpdate = millis();

    brightness += fadeAmount;
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }

    OCR2A = brightness;
    OCR2B = brightness;
  }
}

// breath animation for LED1 only
void handleLed1BreathAnimation() {
  static int brightness = 0;
  static int fadeAmount = 5;
  static unsigned long lastLed1BreathUpdate = 0;

  if (millis() - lastLed1BreathUpdate > 30) {
    lastLed1BreathUpdate = millis();

    brightness += fadeAmount;
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }

    OCR2A = brightness;
  }
}

// breath animation for LED2 only
void handleLed2BreathAnimation() {
  static int brightness = 0;
  static int fadeAmount = 5;
  static unsigned long lastLed2BreathUpdate = 0;

  if (millis() - lastLed2BreathUpdate > 30) {
    lastLed2BreathUpdate = millis();

    brightness += fadeAmount;
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }

    OCR2B = brightness;
  }
}

void setup() {
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN_1, LOW);
  digitalWrite(LED_PIN_2, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  servo1.attach(SERVO_PIN_1);
  servo2.attach(SERVO_PIN_2);
  servo1.write(servoAngle1);
  servo2.write(180 - servoAngle1);  // mirror initial servo position

  Serial.begin(9600);
  IrReceiver.begin(IR_PIN);
  Serial.println("system started...");

  // configure Timer2 for PWM animation
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;

  // set Fast PWM mode
  TCCR2A |= (1 << WGM20) | (1 << WGM21);
  TCCR2B |= (1 << CS21);  // prescaler set to 8

  // enable output for OC2A (LED_PIN_1) and OC2B (LED_PIN_2)
  TCCR2A |= (1 << COM2A1) | (1 << COM2B1);

  OCR2A = 0;  // initial intensity for LED1
  OCR2B = 0;  // initial intensity for LED2

  // configure pins as PWM outputs
  DDRD |= (1 << DDD3);  // set pin 3 (OC2B) as output
  DDRB |= (1 << DDB3);  // set pin 11 (OC2A) as output
}

void loop() {
  // process IR signals
  if (IrReceiver.decode()) {
    unsigned long decodedValue = IrReceiver.decodedIRData.decodedRawData;

    if (decodedValue != 0xFFFFFFFF && decodedValue != 0) {
      Serial.print("valid signal received: 0x");
      Serial.println(decodedValue, HEX);

      if (decodedValue == LED2_AND_BREATH_CODE) {
        if (led2AndBreathState) {
          resetLeds();
          Serial.println("LED2 and LED1 breath animation deactivated");
        } else {
          resetLeds();
          digitalWrite(LED_PIN_2, HIGH);  // turn on LED2
          TCCR2A |= (1 << COM2A1);       // enable PWM for LED1 (breath effect)
          led2AndBreathState = true;
          Serial.println("LED2 on, LED1 breath animation activated");
        }
      }

      if (decodedValue == LED1_AND_BREATH_CODE) {
        if (led1AndBreathState) {
          resetLeds();
          Serial.println("LED1 and LED2 breath animation deactivated");
        } else {
          resetLeds();
          digitalWrite(LED_PIN_1, HIGH);  // turn on LED1
          TCCR2A |= (1 << COM2B1);       // enable PWM for LED2 (breath effect)
          led1AndBreathState = true;
          Serial.println("LED1 on, LED2 breath animation activated");
        }
      }

      if (decodedValue == TOGGLE_LEDS_CODE) {
        toggleLedsState = !toggleLedsState;
        if (toggleLedsState) {
          digitalWrite(LED_PIN_1, HIGH);
          digitalWrite(LED_PIN_2, HIGH);
          Serial.println("both LEDs turned on");
        } else {
          digitalWrite(LED_PIN_1, LOW);
          digitalWrite(LED_PIN_2, LOW);
          Serial.println("both LEDs turned off");
        }
      }

      if (decodedValue == BREATH_ANIMATION_CODE) {
        if (breathAnimationState) {
          resetLeds();
          Serial.println("breath animation deactivated");
        } else {
          resetLeds();
          TCCR2A |= (1 << COM2A1) | (1 << COM2B1); // enable PWM for both LEDs
          breathAnimationState = true;
          Serial.println("breath animation activated");
        }
      }

      if (decodedValue == FAST_BREATH_ANIMATION_CODE) {
        if (fastBreathAnimationState) {
          resetLeds();
          Serial.println("fast breath animation deactivated");
        } else {
          resetLeds();
          TCCR2A |= (1 << COM2A1) | (1 << COM2B1); // enable fast PWM for both LEDs
          fastBreathAnimationState = true;
          Serial.println("fast breath animation activated");
        }
      }

      if (decodedValue == BUZZER_CODE) {
        buzzerState = !buzzerState;
        Serial.println(buzzerState ? "buzzer turned on at 1000 Hz" : "buzzer turned off");
      }

      if (decodedValue == BUZZER_INTERRUPT_CODE) {
        stopBuzzerInterrupt();  // stop buzzer via interrupt
      }

      if (decodedValue == SERVO_PLUS_CODE) {
        cwRotation = !cwRotation;
        ccwRotation = false;
        Serial.println(cwRotation ? "clockwise rotation started" : "clockwise rotation stopped");
      }

      if (decodedValue == SERVO_MINUS_CODE) {
        ccwRotation = !ccwRotation;
        cwRotation = false;
        Serial.println(ccwRotation ? "counter-clockwise rotation started" : "counter-clockwise rotation stopped");
      }
    }
    IrReceiver.resume();
  }

  // handle animations and states
  if (breathAnimationState) {
    handleBreathAnimation();
  }
  if (fastBreathAnimationState) {
    handleFastBreathAnimation();
  }
  if (led2BreathState) {
    handleLed2BreathAnimation();
  }
  if (led1AndBreathState) {
    handleLed2BreathAnimation();  // LED2 breath effect
  }
  if (led2AndBreathState) {
    handleLed1BreathAnimation();  // LED1 breath effect
  }

  // handle servo motors
  if (!breathAnimationState && !fastBreathAnimationState && !led2BreathState && !led1AndBreathState && !led2AndBreathState) {
    handleServoControl();
  }

  // handle buzzer
  handleBuzzer();
}
