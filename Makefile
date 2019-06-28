# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile
CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -std=c++17
LDFLAGS=-g
LDLIBS=

SRCS=Main.cpp MineSweeper.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: MineSweeper

MineSweeper: $(OBJS)
	$(CXX) $(LDFLAGS) -o MineSweeper $(OBJS) $(LDLIBS) 

Main.o: Main.cpp MineSweeper.hpp

MineSweeper.o: MineSweeper.hpp MineSweeper.cpp

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) tool
