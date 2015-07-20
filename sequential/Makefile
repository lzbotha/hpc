CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -O3 -std=c++11 $(shell root-config --cflags)
LDFLAGS=-g -O3 $(shell root-config --ldflags)
LDLIBS=$(shell root-config --libs)

SRCS=main.cpp utils.cpp grid.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: tool

tool: $(OBJS)
	$(CXX) $(LDFLAGS) -o tool $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .depend

include .depend