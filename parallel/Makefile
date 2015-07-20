CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-O3 -std=c++11 -fopenmp
LDFLAGS=-link -O3
LDLIBS=-lgomp -lcudart

SRCS=main.cpp utils.cpp
OBJS=main.o utils.o grid.o

all: tool

tool: $(OBJS)
	nvcc $(LDFLAGS) -o tool $(OBJS) $(LDLIBS) -arch=sm_20

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

grid.o: grid.cu grid.h
	nvcc -O3 -lgomp -lcudart  -Xcompiler -fopenmp -o grid.o -c grid.cu -arch=sm_20

clean:
	$(RM) main.o utils.o grid.o

dist-clean: clean
	$(RM) *~ .depend

include .depend