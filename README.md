# MorseCar

## Components:##

STM32 Board: The STM32F401 is a microcontroller. It is used to execute the firmware needed for the project. Two STM microcontrollers are needed for the project. One is needed for the controller module, whilst the other is required for the car module. The controller STM32 will only be connected to a button and a NRF24L01 chip. In this case, its purpose will be to get inputs from the button and output them to the NRF24L01 chip which will then send these inputs to the car module. The car module STM32 will be connected to a NRF24L01 chip, a L298 module, ultrasonic sensors, and LEDS. It receives inputs from the NRF24L01 chip which will be configured to collect signals from the other NRF24L01 chip attached to the controller. These inputs which will be in morse code will be processed by the STM32 and act as instructions for how the car will move. The STM32 will then output these instructions to the L298 module.

NRF24L01 radio chip: The NRF24L01 is a single chip radio transceiver that communicates on the 2.4Ghz band. This specific chip was chosen for this project because it is compatible with a variety of microcontrollers, including the STM32. In this project, 2 NRF24L01 chips will be used in order to have communication between the car and the controller. The NRF24L01 connected to the controller board will be set up to send signals. The NRF24L01 connected to the car board will be set up to receive signals.

L298N driver module: The L298 is a driver module capable of driving DC motors. Furthermore, the driver module is able to control up to 4 DC motors. This module was chosen for the project since it is able to control the 4 DC motors being used for the car.  

HC-SR04:The HC-SR04 is an ultrasonic sensor that acts as a transmitter which converts to electrical signals. This sensor is ideal for this project as it offers excellent contact range between 2cm to 400cm. It uses ultrasonic sound waves to detect distance and returns it to detect the distance. 
