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


#make build and bin folder if they dont already exist
make_build:
	@mkdir -p $(build_dir)

make_bin:
	@mkdir -p $(bin)

all: $(Name)

$(Name): make_bin ascii main calculation parse
	$(CC) $(Flags)  $(build_dir)/main.o $(build_dir)/ascii.o $(build_dir)/parse.o $(build_dir)/calculations.o -o $(bin)/$(Name)

#construct main
main: make_build
	$(CC) $(Flags) -c $(source)/main.cpp -o $(build_dir)/main.o

#construct ascii
ascii:  make_build
	$(CC) $(Flags) -I$(lib_dir) -c $(source)/ascii.cpp -o $(build_dir)/ascii.o

#construct parse
calculation: make_build
	$(CC) $(Flags) -I$(lib_dir) -c $(source)/calculations.cpp -o $(build_dir)/calculations.o

#construct parse
parse: make_build
	$(CC) $(Flags) -I$(lib_dir) -c $(source)/parse.cpp -o $(build_dir)/parse.o

#clear binary files
clear:
	rm -rf ./bin/*

#clear builds
clean:
	rm -rf ./build/*.o main 
