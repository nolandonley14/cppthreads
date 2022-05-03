# Define the makefile variables that will be used in building system

F90 = gfortran
CC  = gcc
FFLAGS = -cpp -O2 
CFLAGS = -g -std=c++20
MYLIBS = -L./cppthreads -lcppthreads_bblas -L./lbstime -llbstime
OBJS = array.o walltime.o cputime.o tprod.o
SYSLIBS = -L/usr/lib64 -pthread -lstdc++
