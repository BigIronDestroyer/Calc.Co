#compiler
CC=g++

#source directory
source=./src

#build directory
build_dir=./build

#lib source
lib_dir=./include

# bin directory
bin=./bin
#Flags
Flags=-Wall -Wextra -std=c++17

#project name
Name=CalcCo

all: $(Name)

$(Name): ascii main calculation parse
	$(CC) $(Flags)  $(build_dir)/main.o $(build_dir)/ascii.o $(build_dir)/parse.o $(build_dir)/calculations.o -o $(bin)/$(Name)

#construct main
main:
	$(CC) $(Flags) -c $(source)/main.cpp -o $(build_dir)/main.o

#construct ascii
ascii: 
	$(CC) $(Flags) -I$(lib_dir) -c $(source)/ascii.cpp -o $(build_dir)/ascii.o

#construct parse
calculation:
	$(CC) $(Flags) -I$(lib_dir) -c $(source)/calculations.cpp -o $(build_dir)/calculations.o

#construct parse
parse:
	$(CC) $(Flags) -I$(lib_dir) -c $(source)/parse.cpp -o $(build_dir)/parse.o

#clear binary files
clear:
	rm -rf ./bin/*

#clear builds
clean:
	rm -rf ./build/*.o main 
