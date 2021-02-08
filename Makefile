CFLAGS	= -Wall -Wextra -pedantic -std=c99
LDFLAGS	= -L/usr/local/lib
LDLIBS	= -lm -lSDL2

sources = src/main.c src/mem.c src/cpu.c
headers = src/include/mem.h src/include/cpu.h src/utils/misc.h

all: bin/emulator.out
	
bin/emulator.out: $(sources) $(headers)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(sources) $(LDLIBS)


clean:
	rm -rf bin
