CFLAGS=-fPIC

all: libpi.a

libpi.a: dd.o
	ar rs $@ $<

dd.o: dd.c
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: all clean

clean:
	\rm *.o *.a

# vim: set noexpandtab:
