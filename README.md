# VGA output using an STM32F3-Discovery board
The objective of this project was to utilize an STM32F3-Discovery board (STM32F303VC) for the transmission of VGA video signals to a monitor. To achieve this goal, we developed an application leveraging the Hardware Abstraction Layer (HAL) provided in the STM32Cube package, in combination with emWin libraries. Additionally, we designed a custom adapter to establish the connection between the VGA pins and the STM board.
Documentation (in Italian) is currently available in the [Wiki](https://github.com/lucavivenzo/VGA-STM32F3-Discovery/wiki).

# Demo
A video showing the demo is available on [Youtube](https://www.youtube.com/watch?v=aGSfR4g1vQc).
The block diagram is shown below, along with the output we displayed on the screen in the Demo application.
![Block Diagram](https://i.imgur.com/hPxTZJF.jpeg)
![Demo Video Output](https://i.imgur.com/semI2Es.png)

## How to run the Demo
After downloading STM32CubeF3, specify its path in the Makefile (the root directory is `STM_DIR`).

Modify the `LIBS` and `LIB` variables in the makefile in order to point at your own copy of the emWin library.

To compile the project, run the following code in `p1Gruppo13`:
```
$ make prepare
$ make
```
# Contributors
- Carmine Marra 
- Francesco Maria Papulino
- Simone Staiano 
- Luca Vivenzo
