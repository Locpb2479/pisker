<p align="center">
    <a href="https://github.com/Locpb2479/pisker"><img src="https://img.shields.io/badge/release-v1.2.0-blue"></a>
    <a href=""><img src="https://img.shields.io/badge/language-C/C++-aff.svg"></a>
    <a href="https://www.st.com/en/development-tools/stm32cubeide.html"><img src="https://img.shields.io/badge/ide-STM32CubeIDE-pink.svg"></a>
    <a href="https://itrvn.com/"><img src="https://img.shields.io/badge/source-ITR%20VN-yel.svg"></a>

</p>

Pisker is an intern project of ours at [ITR VN](https://itrvn.com/).

## Learn More about Pisker 
 <!-- <p align="center">
  <img src="./intro.gif" alt="Project Image" width="600" height="auto">
</p> -->

## Table of Contents
- [Learn More about Pisker](#learn-more-about-pisker)
- [Table of Contents](#table-of-contents)
- [Technologies](#technologies)
- [Features](#features)
- [Usage](#usage)
- [Contributing](#contributing)
<!-- - [License](#license) -->
<!-- - [Demo Smart Desk Clock](#demo-smart-desk-clock) -->




## Technologies
 <!-- <p align="center">
  <img src="./tech.jpg" alt="Project Image" width="500" height="auto">
</p> -->

* **STM32 Microcontroller**: The project is based on the STM32 microcontroller platform, which offers a wide range of microcontrollers with different performance levels and features.
*  **STM32CubeIDE**: The project was developed using popular IDEs which is STM32CubeIDE, provide tools for code development, debugging, and firmware deployment.
*  **Communication Protocols**: The project includes the implementation of communication protocols such as UART, I2C.
*  **Peripheral Libraries**: The project utilizes peripheral libraries provided by the microcontroller manufacturer or third-party libraries to simplify the integration and configuration of peripherals.
*  **Other Device**: We intergrated a lot of device to increase experiment of customer and performance of device.
*  See our [document](./doc/feature_of_project.md) and [system architecture](./doc/firmware_architechture.png).

## Features
 <!-- <p align="center">
  <img src="./Description.jpg" alt="Project Image" width="700" height="auto">
</p> -->
The SmartDeskClock includes Includes new capabilities such as:

1. **Time Display**: The device can display the time (hours, minutes, seconds) and date on the screen.

2. **Alarm and Notifications**: The clock can set timers, alarm, countdowns.

3. **Music player**: User can play music via SD card.

4. **Rhythm light**: Device can display sound wave of the music.
5. Read our [release note](./RELEASE_NOTE.md) for more details and Look forward to other exciting features in the future . 

## Usage
1. Clone the project repository from [GitHub ↗](https://github.com/Locpb2479/pisker).
2. Set up your development environment with the required IDE (STM32CubeIDE) and toolchain and open the project in the chosen IDE.
3. Read our [diagram](./doc/diagram_wire_connection.jpg) to connect the necessary peripherals or sensors to the STM32 microcontroller.
4. Deploy the firmware to the STM32 microcontroller using the appropriate flashing method (e.g., ST-Link, DFU, or bootloader).

## Contributing
We welcome contributions to this project! To ensure a smooth contribution process, please follow the guidelines below:

1. Make sure you have read and understood the Contribution Guide before getting started.
2. Check the Issues to see if there are any existing issues or requested features.
3. Create a new branch from main to work on your new feature: git checkout -b new-feature.
4. Make the necessary changes, additions, or bug fixes in the source code.
5. Double-check the code to ensure there are no errors and that it follows the coding guidelines.
6. Create a Pull Request with a detailed description of the changes you have made.
7. Wait for feedback and make any requested changes from the code reviewer.
8. Once your Pull Request is approved, thank you for your contribution and support!
* **Note**: Contributions to this project are welcome. If you find any issues or have suggestions for improvements, please submit a pull request or open an issue on the project's [GitHub repository](https://github.com/Locpb2479/pisker).
