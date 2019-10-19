
# Disable implicit rules and variables
MAKEFLAGS+=--no-builtin-rules --no-builtin-variables

# CXX?=g++ means that it will use g++ if the variable is not already defined
CXX?=g++
CXXFLAGS=-Wall -Wextra -O0 -g -MMD
# Don't forget to add mingw32 and SDL2main when building for window
LDLIBS=-lmingw32 -lSDL2main -lSDL2

SRCS=main.cpp
OBJS=$(SRCS:.cpp=.o)
DEPS=$(SRCS:.cpp=.d)

.PHONY: all clean

all: main

-include $(DEPS)

main: $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

clean:
	rm -f main $(OBJS) $(DEPS)

