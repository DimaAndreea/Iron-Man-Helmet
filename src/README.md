# About


<details>
  <summary> <h2> Current Implementation Status </h2> </summary>
  
  ##

  The project is currently functional and implements most of the specified requirements. Features include:

  - LED control with animations: Slow and fast breathing effects, along with various combinations.
  - Buzzer functionality: The buzzer currently emits a single frequency, and an interrupt is implemented to stop it in real-time.
  - Bidirectional control of servomotors: Supports clockwise and counter-clockwise rotation with precise angle adjustments.
  - Interrupt handling: Interrupt functionality is implemented for the buzzer, allowing it to be stopped immediately upon receiving a specific IR command.

  The system responds promptly to IR commands and demonstrates effective use of interrupts for real-time control. However, the melody playback functionality for the buzzer is yet to be implemented.
  
##
</details>


<details>
  <summary> <h2> Used Libraries </h2> </summary>
  
  ##

  - <Arduino.h>: Essential for microcontroller programming, providing core functions like digitalWrite, analogWrite, and millis.
  - <IRremote.h>: A robust and well-documented library for receiving and decoding IR signals, simplifying command processing.
  - <Servo.h>: Facilitates precise and efficient control of servomotors, abstracting the complexities of PWM signal generation. These libraries reduce code complexity and enhance maintainability.
  
##
</details>


<details>
  <summary> <h2> Used Functionalities from Lab </h2> </summary>
  
  ##

  1. Used GPIO pins.
  2. USART:  Used via the serial monitor to debug IR signals and display informative messages during operation.
  3. Interrupts: Implemented for immediate stopping of the buzzer based on IR command.
  4. Timing with millis(): Used for synchronizing animations and servo movements without blocking the main program.
  5. PWM: Employed for LED animations and precise servo control.


  
##
</details>




<details>
  <summary> <h2> Code Structure </h2> </summary>
  
  ##

 The project is structured as follows:

- Hardware Initialization: Configures pins, enables PWM, and initializes objects (IR receiver and servos).
- Main Loop (loop): Processes IR commands, handles LED animations, plays buzzer melodies, and manages servo control.
- Dedicated Functions: Separate functions for resetting LEDs, managing animations, handling the buzzer, and controlling servos. Validation:

  Each functionality was tested independently to ensure accurate response to IR commands.
Interrupts were simulated and verified to immediately stop LEDs and the buzzer.


##
</details>





<details>
  <summary> <h2> Optimizations Made </h2> </summary>
  
  ##

 - Minimized Latency: Used millis() instead of delay for synchronized and non-blocking actions. These optimizations improve overall performance and scalability of the project.
 - Code Structuring: Organized features into dedicated functions, improving readability and maintainability.
 - Hardware PWM: Reduced processor load for LED animations by leveraging hardware timers.
 - Efficient Interrupts: Ensured the buzzer could be stopped immediately without disrupting other functionalities.


##
</details>



<details>
  <summary> <h2> Demo Vide </h2> </summary>
  
  ##

 TBD


##
</details>
