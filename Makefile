CC = gcc
CFLAGS = -O3
LDFLAGS = -lm
EXES = ppmtest

all: $(EXES)

ppmtest: ppm_test.c ppm.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -rf *.o *.gch $(EXES)
