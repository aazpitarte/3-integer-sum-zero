
CC = g++
FILES = sum_to_zero.cpp
FLAGS = -std=c++11 -g
EXE = run

all: $(FILES) catch.hpp
	$(CC) $(FILES) -o $(EXE) $(FLAGS)

clean:
	rm run.exe
	
