# Top level makefile
#
include Makefile.inc

all : driver cppthreads lbstime

driver: driver.o cppthreads
	$(F90) driver.o -o driver $(MYLIBS) $(SYSLIBS)

driver.o: driver.f90
	$(F90) $(FFLAGS) driver.f90 -c

cppthreads:
	cd cppthreads && $(MAKE)

lbstime:
	cd lbstime && $(MAKE)

clean:
	cd cppthreads && $(MAKE) clean
	cd lbstime && $(MAKE) clean
	rm *.o
	touch *.f90

pristine:
	cd cppthreads && $(MAKE) pristine
	cd lbstime && $(MAKE) pristine
	rm *.o
	rm driver
	touch *.f90

#This next target get "made" every time
.PHONY: cppthreads lbstime
