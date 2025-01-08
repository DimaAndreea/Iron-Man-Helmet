## About


| Component           | Pin(s)       |
|---------------------|--------------|
| White LEDs  | 3, 11 (PWM)  | Timer 2     
| Servomotors         | 9, 10 (PWM)  | 
| Passive Buzzer      | 6            |
| IR Sensor           | 2            | 


* The project is built around an Arduino Nano, chosen for its compact size to save space inside the helmet. The main functionalities are controlled via an IR remote and include two servomotors for lifting the faceplate, two white LEDs for eye illumination, and a passive buzzer for sound effects. The hardware components are connected to specific pins on the Arduino Nano, as shown below:

  - White LEDs: Connected to pins 3 and 11 (PWM pins) and controlled via Timer 2. Each LED is paired with a 220-ohm resistor to limit current and prevent damage. The LEDs use PWM signals to create a "breathing" light effect, where the brightness gradually increases and decreases for a smooth and realistic visual appearance.
  - Servomotors: Connected to pins 9 and 10 (PWM pins), utilizing Timer 1. These motors are powered by a separate 6V power supply (4 AA batteries) to ensure sufficient current, as the Arduino's main power source was insufficient.
  - Passive Buzzer: Connected to pin 6, using Timer 0 to generate tones for sound effects.
  - IR Sensor: Connected to pin 2, utilizing the INT0 interrupt for receiving and decoding signals from the IR remote. The communication is based on 38 kHz infrared modulation.

* The Arduino Nano is powered by 4 AA batteries (6V), which provide the required voltage for the microcontroller. By powering the servomotors from a separate 6V supply, power-related issues are eliminated, ensuring reliable and smooth operation.

* The communication between the components involves PWM signals for the LEDs and servomotors, and interrupt-based decoding for the IR sensor. 

<details>
  <summary> <h2>  Bill of Materials </h2> </summary>
  
##
  
 
| Quantity | Material     | Link to shop     | Datasheet   |
|:--------------:|:-----------------:|--------------:|----------------|
| 1 | Arduino Nano (ATmega328P + CH340)  | [Shop Link ](https://www.optimusdigital.ro/en/compatible-with-arduino-nano/1686-development-board-arduino-nano-compatible-atmega328p-ch340.html?search_query=arduino+nano&results=29)  | [Datasheet ](http://www.ee.ic.ac.uk/pcheung/teaching/DE1_EE/stores/sg90_datasheet.pdf)  |
|  1    |  Passive Buzzer 5V | [Shop Link ](https://www.optimusdigital.ro/en/buzzers/634-5v-passive-buzzer.html?search_query=buzzer&results=87) | [Datasheet ](https://www.farnell.com/datasheets/2171929.pdf) |
|  2    | White LED  | [Shop Link ](https://www.optimusdigital.ro/en/leds/930-5-mm-white-led-with-clear-lens.html?search_query=led+5mm&results=476) | [Datasheet ](https://www.farnell.com/datasheets/2861562.pdf) |
|  2    | Servo Motor (SG90) | [Shop Link ](https://www.optimusdigital.ro/en/servomotors/2261-micro-servo-motor-sg90-180.html?search_query=sg90&results=12) | [Datasheet ](http://www.ee.ic.ac.uk/pcheung/teaching/DE1_EE/stores/sg90_datasheet.pdf) |
|  2    | 4x AA Battery Holder | [Shop Link ](https://www.sigmanortec.ro/Suport-4-baterii-AA-cu-capac-si-intrerupator-p172447738) | x |
|  2    | 220Ω Resistor | [Shop Link ](https://www.optimusdigital.ro/en/resistors/856-025w-220k-resistor.html?search_query=resistor+220&results=46) | x |
|  1    | IR Remote and Reciever Kit | [Shop Link ](https://www.optimusdigital.ro/en/kits/4780-infrared-remote-and-receiver-module-kit.html?search_query=Infrared+Remote+and+Receiver+Module+Kit&results=2) |[Datasheet ](https://www.datasheetcafe.com/chq1838-datasheet-infrared-receiver/) |

##
</details>



<details>
  <summary> <h2>  Block Diagram </h2> </summary>
  
##


![block_diagram](https://github.com/user-attachments/assets/20b7db20-4d2f-4443-b45f-51bafc3c9d41)

  ##
</details>





<details>
  <summary> <h2>  Circuit Diagram </h2> </summary>
  
##


![Copy of Arduino Nano (3)](https://github.com/user-attachments/assets/76468681-3e60-46c0-83ad-dc33c7ba61e5)


  ##
</details>


<details>
  <summary> <h2>  Video Test </h2> </summary>
  
##

[![Watch the video](https://img.youtube.com/vi/ticRafRHYcw/maxresdefault.jpg)](https://www.youtube.com/watch?v=ticRafRHYcw)



  ##
</details>
