CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -std=c++11 $(shell root-config --cflags)
LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=-lcppunit $(shell root-config --libs)

SRCS=main.cpp test_utils.cpp test_grid.cpp ../utils.cpp ../grid.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: tests

tests: $(OBJS)
	$(CXX) $(LDFLAGS) -o tests $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .depend

include .depend