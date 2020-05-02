# 1BitsyLab - STM32F415RGT6
Learning STM32 programming with the 1Bitsy + BMP

## Working with CLion

This repo is setup to use both Make and CMake. CMake support was added for CLion, which can build and debug the labs. Most info was taken from [this repo](https://github.com/StanislavLakhtin/clion_freertos_stm32f103_template). Currently the `.gdbinit` file in the repo root needs to be copied to your home directory. This needs to be fixed, possibly by [this](https://github.com/nagelkl/clion_embedded/blob/master/setup_gdbinit.bat) workaround.


## Flashing

1) Connection the BMP to the target

2) Browse to the working lab directory

    $ make flash


## Debugging

From the [quickstart](https://1bitsy.org/overview/quickstart/) guide.

1) Find BMP serial device

    $ ls /dev/cu.usbmodem*

2) Boot up GDB with an elf file

    $ arm-none-eabi-gdb miniblink.elf

3) Connect to BMP in GDB

    (gdb) target extend-remote /dev/cu.usbmodemXXXXX1
    (gdb) monitor version

4) Find and attach to the 1Bitsy using JTAG

    (gdb) monitor jtag_scan
    (gdb) attach 1

5) Upload and run the code

    (gdb) load
    (gdb) run

6) Explore your code with GDB!


## Tasks

### Basics

- [x] Get to [miniblink](https://github.com/1Bitsy/1bitsy-examples/tree/master/examples/1bitsy/miniblink)
- [x] Push a [Button](https://github.com/1Bitsy/1bitsy-examples/tree/master/examples/1bitsy/button)

STM32 Youtube Channel

- [ ] PWM LED [Fade](https://github.com/1Bitsy/1bitsy-examples/blob/master/examples/1bitsy/pwmledfade/pwmledfade.c)
- [ ] [USART](https://github.com/1Bitsy/1bitsy-examples/blob/master/examples/1bitsy/usart/usart.c)

### Intermediate

- [ ] Write LCD display driver (SSD1306)
[Examples](https://github.com/1Bitsy/1bitsy-examples/tree/master/examples/1bitsy)

### Hard

- [ ] Miniblink with ASM
- [ ] Interface with RGB LEDs
- [ ] Implement PID algorithm

### Understand your Tools

- [ ] Get good at using GDB
- [ ] Understand the linker file
- [ ] Understand what an ELF file is
- [ ] Understand how your Makefile works




## Useful References
In case of being stuck

http://sgreg.fi/blog/article/bare-metal-arm-cortexm-hello-world-on-linux  
https://rhye.org/post/stm32-with-opencm3-0-compiling-and-uploading/  
https://bdebyl.net/post/stm32-part0/  
