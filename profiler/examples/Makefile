CXX = g++
CXXFLAGS = -std=c++17
INC_PATH_HPP +=../include

CC = gcc
CFLAGS = -g
LDFLAGS = ../adapter
INC_PATH_H += ../adapter/include

profiler_cpp: main.cpp
	${CXX} ${CXXFLAGS} -I${INC_PATH_HPP} main.cpp -o profiler -lpthread

profiler_c: main.c
	${CC} ${CFLAGS} -I${INC_PATH_H} -L${LDFLAGS} main.c -o profiler_c -lprofiler_adapter

all: profiler_cpp profiler_c

clean:
	rm -f profiler profiler_c