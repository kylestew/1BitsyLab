# 1BitsyLab - STM32F415RGT6
Learning STM32 programming with the 1Bitsy + BMP

## Programming

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

- [ ] Get to [miniblink](https://github.com/1Bitsy/1bitsy-examples/tree/master/examples/1bitsy/miniblink)
- [ ] Push a [Button](https://github.com/1Bitsy/1bitsy-examples/tree/master/examples/1bitsy/button)

### Intermediate

[Examples](https://github.com/1Bitsy/1bitsy-examples/tree/master/examples/1bitsy)

### Hard

- [ ] Implement PID algorithm


### Understand your Tools

- [ ] Get good at using GDB
- [ ] Understand the linker file
- [ ] Understand what an ELF file is
- [ ] Understand how your Makefile works

### Understand ASM

- [ ] Blinky with ASM only




## Useful References
In case of being stuck

http://sgreg.fi/blog/article/bare-metal-arm-cortexm-hello-world-on-linux  
https://rhye.org/post/stm32-with-opencm3-0-compiling-and-uploading/  
https://bdebyl.net/post/stm32-part0/  
https://github.com/kylestew/bluepill-example  
