include ../Makefile.inc

# C++ Threads library targets 

all: lib

mmm.o : mmm.cpp
	$(CC) $(CFLAGS)  -c mmm.cpp

vvm.o : vvm.cpp
	$(CC) $(CFLAGS)  -c vvm.cpp

lib: mmm.o vvm.o 
	ar -rc libcppthreads_bblas.a  mmm.o vvm.o 
	ranlib libcppthreads_bblas.a

# Default Targets for Cleaning up the Environment

clean :
	rm *.o
	touch *.c

pristine:
	make clean
	rm *.a
