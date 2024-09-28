#compiler
CC = g++

#Flags
Flags = -Wall -c

all: main

main:
    $(CC) ./src/main.cpp -o ./bin/main

clean:
    rm -rf ./bin/*.o main