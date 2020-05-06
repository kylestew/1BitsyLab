


https://github.com/lochsh/gpio-toggle-exercise



## Building

    $ arm-none-eabi-as -mcpu=cortex-m4 toggle.s -c -o output/toggle.o


## Linking

    $ arm-none-eabi-ld -T link.ld output/toggle.o -o output/toggle


