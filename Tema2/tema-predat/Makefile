# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS = my_octave 

build: $(TARGETS)

tema: my_octave.c
	$(CC) $(CFLAGS) my_octave.c -lm -o my_octave

pack:
	zip -FSr 314CA_OprisanAlexiaIoana_Tema2.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean