GCC = gcc
AR = ar
FLAGS = -Wall -g

all:  frequency

frequency: frequency.c
	$(GCC) $(FLAGS) frequency.c -o frequency

.PHONY: clean

clean:
	rm -f *.o frequency
	rm -f *.out