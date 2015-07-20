CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -std=c++11
LDFLAGS=-link -lineinfo --generate-line-info -g
LDLIBS=-lgomp -lcudart -lcppunit

SRCS=main.cpp test_utils.cpp test_grid.cpp ../utils.cpp
OBJS=main.o test_utils.o test_grid.o ../utils.o ../grid.o

all: tests

tests: $(OBJS)
	nvcc $(LDFLAGS) -o tests $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

../grid.o: ../grid.cu ../grid.h
	nvcc -m64 -Xcompiler -fopenmp -Xcompiler -lineinfo --generate-line-info -O3 -DFLOAT -DFORUM -use_fast_math -prec-div=false -ftz=true -prec-sqrt=false --fmad=true -o ../grid.o -c ../grid.cu

clean:
	$(RM) main.o test_utils.o test_grid.o ../utils.o ../grid.o

dist-clean: clean
	$(RM) *~ .depend

include .depend