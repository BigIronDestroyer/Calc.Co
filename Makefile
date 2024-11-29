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

$(Name): make_bin ascii main calculation parser tokenizer
	$(CC) $(Flags)  $(build_dir)/main.o $(build_dir)/ascii.o $(build_dir)/parser.o $(build_dir)/calculations.o $(build_dir)/tokenizer.o -o $(bin)/$(Name)

#construct main
main: make_build
	$(CC) $(Flags) -c $(source)/main.cpp -o $(build_dir)/main.o

#construct ascii
ascii:  make_build
	$(CC) $(Flags) -I$(lib_dir) -c $(source)/ascii.cpp -o $(build_dir)/ascii.o

#construct calculation
calculation: make_build
	$(CC) $(Flags) -I$(lib_dir) -c $(source)/calculations.cpp -o $(build_dir)/calculations.o

#construct parser
parser: make_build
	$(CC) $(Flags) -I$(lib_dir) -c $(source)/parser.cpp -o $(build_dir)/parser.o
	
#construct parse
tokenizer: make_build
	$(CC) $(Flags) -I$(lib_dir) -c $(source)/tokenizer.cpp -o $(build_dir)/tokenizer.o


#clear binary files
clear:
	rm -rf ./bin/*

#clear builds
clean:
	rm -rf ./build/*.o main 
