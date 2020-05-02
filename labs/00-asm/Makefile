OUT=output/gpio-toggle
all: $(OUT)

$(OUT): gpio-toggle.s link.ld
	mkdir -p output
	arm-none-eabi-as -mcpu=cortex-m4 gpio-toggle.s -c -o output/gpio-toggle.o
	arm-none-eabi-ld -T link.ld output/gpio-toggle.o -o $@

flash: $(OUT)
	arm-none-eabi-gdb -n --batch 				\
		-ex 'tar ext /dev/tty.usbmodemD5DB7BE81'  		\
		-ex 'mon tpwr en'					\
		-ex 'mon swdp_scan'					\
		-ex 'att 1' 						\
		-ex 'load' 							\
		-ex 'start' 						\
		-ex 'detach' 						\
		-ex 'quit' 						\
		$<

clean:
	rm -rf output


