
all: libpi.a

libpi.a: dd.o
	ar rs $@ $<

dd.o: dd.c

.PHONY: all clean

clean:
	\rm *.o *.a

# vim: set noexpandtab:
