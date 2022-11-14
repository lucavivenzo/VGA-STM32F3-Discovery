# VGA output using an STM32F3-Discovery board
The goal of this project was to design and build an application based on the Hardware Abstraction Layer (HAL) and STemWin libraries available in the STM32Cube package. We decided to build a VGA interface for an STM32F3-Discovery board (STM32F303VC) to send video signals to a Monitor, displaying images on the screen as a proof of concept.
Documentation is currently available in the internal [Wiki](http://www.naplespu.com/es/index.php?title=Sviluppo_di_un%27applicazione_basata_su_middleware_STM32Cube:_graphics,_display_(VGA/HDMI))

# Demo
A video showing the demo is available on [Youtube](https://www.youtube.com/watch?v=aGSfR4g1vQc)
The block diagram is shown below, along with the output we displayed on the screen in the Demo application.
![Block Diagram](https://i.imgur.com/hPxTZJF.jpeg)
![Demo Video Output](https://i.imgur.com/semI2Es.png)

## How to run the Demo
After downloading STM32CubeF3 (in the Makefile, the root directory is `STM_DIR`) move the contents of this repository inside `$STM_DIR\Projects\STM32F3-Discovery`. Some changes to the variables `STM_DIR` and `DEM_DIR` in the Makefile are necessary to compile for a specific board.

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
