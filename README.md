# Autonomous Car Control System

## Table of Contents
- [Project Overview](#project-overview)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Installation](#installation)
- [Project Structure](#project-structure)
- [Functionality](#functionality)
  - [Lane Keeping Assistance (LKS)](#lane-keeping-assistance-lks)
  - [Adaptive Cruise Control (ACC)](#adaptive-cruise-control-acc)
  - [Automatic Braking (AB)](#automatic-braking-ab)
  - [Bluetooth Communication](#bluetooth-communication)
  - [Adaptive Lighting Control (ALC)](#adaptive-lighting-control-alc)
- [Contributing](#contributing)
- [License](#license)

## Project Overview
The goal of this project is to develop a real-time operating system (RTOS)-based control system for an autonomous car. The system is capable of:
- Maintaining lane position
- Adjusting speed based on the distance to the vehicle in front
- Automatically braking to avoid collisions
- Receiving control commands via Bluetooth
- Adjusting headlights based on ambient light conditions

## Hardware Requirements
- STM32 microcontroller (e.g., STM32F4 series)
- Motor driver
- Infrared sensors for lane detection
- Ultrasonic sensor for distance measurement
- Bluetooth module (e.g., HC-05)
- Light Dependent Resistor (LDR) for ambient light sensing
- LEDs for turn signals and status indicators

## Software Requirements
- STM32CubeMX
- STM32CubeIDE
- FreeRTOS
- HAL (Hardware Abstraction Layer) libraries

## Installation
1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/autonomous-car-control-system.git
   cd autonomous-car-control-system
2. Open the project in STM32CubeIDE.
3. Generate code using STM32CubeMX and make sure FreeRTOS is included.
4. Build and flash the code onto the STM32 microcontroller.
## Project Structure
    autonomous-car-control-system/
├── Core/
│   ├── Inc/
│   │   ├── main.h
│   │   ├── freertos.h
│   │   └── stm32f4xx_hal_conf.h
│   ├── Src/
│   │   ├── main.c
│   │   ├── freertos.c
│   │   └── stm32f4xx_it.c
├── Drivers/
│   ├── CMSIS/
│   ├── HAL_Driver/
│   └── BSP/
├── Middlewares/
│   └── Third_Party/
│       └── FreeRTOS/
├── README.md
└── LICENSE

## Functionality

### Lane Keeping Assistance (LKS)
The LKS system uses infrared sensors to detect lane markings and adjusts the car's direction to stay within the lane. It has two modes:
- **Standard Mode:** Alerts the driver when the car drifts out of the lane.
- **Adaptive Mode:** Automatically steers the car to keep it within the lane.

### Adaptive Cruise Control (ACC)
The ACC system uses an ultrasonic sensor to measure the distance to the vehicle in front and adjusts the car's speed to maintain a safe following distance. It has the following characteristics:
- **Minimum Distance:** 5 cm
- **Default Distance:** 20 cm
- **Maximum Speed:** 80%

### Automatic Braking (AB)
The AB system automatically stops the car if an obstacle is detected within a 10 cm range, preventing collisions.

### Bluetooth Communication
The Bluetooth module allows for manual control of the car via a mobile app. The following commands are supported:
- Move forward
- Move backward
- Turn left
- Turn right
- Adjust speed
- Turn signals on/off
- Enable/disable LKS and ACC

### Adaptive Lighting Control (ALC)
The ALC system uses an LDR to adjust the car's headlights based on ambient light conditions. The headlights can operate at maximum, adaptive, or low lighting levels, or be turned off.

## Contributing
Contributions are welcome! Please submit a pull request or open an issue to discuss your ideas or bug fixes.

## License
This project is licensed under the terms that can be found in the LICENSE file in the root directory of this software component. If no LICENSE file comes with this software, it is provided AS-IS.
