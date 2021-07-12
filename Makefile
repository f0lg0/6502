CFLAGS	= -Wall -Wextra -pedantic -std=c99
LDFLAGS	= -L/usr/local/lib
LDLIBS	= -lm -lncurses

sources = src/main.c src/mem/mem.c src/cpu/cpu.c src/cpu/instructions.c src/peripherals/interface.c src/peripherals/kinput.c
headers = src/mem/mem.h src/cpu/cpu.h src/cpu/instructions.h src/peripherals/interface.h src/peripherals/kinput.h src/utils/misc.h

all: bin/emulator.out
	
bin/emulator.out: $(sources) $(headers)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(sources) $(LDLIBS)


clean:
	rm -rf bin
