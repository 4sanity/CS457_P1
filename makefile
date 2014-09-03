#Sam Bruns
#Project 1
#Date: 9/3/2014
#Makefile for 457 Project 1

CC = g++

CC_SRCS = chat.cpp

EXE = chat

CC_FLAGS = -g -Wall

#compiles C++ source files into an executable
make:
    #@echo "Compiling C++ source file and creating executable..."
	$(CC) $(CC_SRCS) $(CC_FLAGS) -o $(EXE)
	@echo ""

#cleans up directory
clean:
    #@echo "Cleaning up project directory ..."
	rm -f *.o $(EXE) core chat
	@echo ""