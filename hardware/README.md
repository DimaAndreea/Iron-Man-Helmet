## About


| Component           | Pin(s)       | Timer |
|---------------------|--------------|------------------------------------------------------|
| White LEDs  | 3, 11 (PWM)  | Timer 2              |
| Servomotors         | 9, 10 (PWM)  | Timer 1   |
| Passive Buzzer      | 6            | Timer 0                      |
| IR Sensor           | 2            | INT0 interrupt     |



* In this project, an Arduino Nano is used to create an Iron Man helmet with interactive features. The white LEDs for the eyes are connected to PWM pins 3 and 11, chosen for their ability to support a breathing animation effect. The servomotors, used to lift the faceplate and move simultaneously, are connected to PWM pins 9 and 10, as these pins enable precise and synchronized motor control. A 5V passive buzzer is connected to pin 6 to produce sound effects, and an IR sensor is connected to pin 2, utilizing the INT0 interrupt for efficient and reliable response to commands from an IR remote.

* These pin assignments were chosen to make the best use of the Arduino Nano’s timers: timer 0 is used for the buzzer, timer 1 controls the servos, and timer 2 handles the LEDs. The Arduino is powered by four AA batteries, but the servos required a separate power source (another set of four AA batteries) to prevent circuit instability caused by their high current draw.




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

![block_diagram](https://github.com/user-attachments/assets/f789251e-5095-4b0a-b99f-d872d8ec4e21)


  ##
</details>





<details>
  <summary> <h2>  Circuit Diagram </h2> </summary>
  
##


![Copy of Arduino Nano (3)](https://github.com/user-attachments/assets/76468681-3e60-46c0-83ad-dc33c7ba61e5)


  ##
</details>
