#the files to compile as part of project
OBJS = main.cpp res/mat2.cpp res/vec2.cpp res/menu.cpp

#the compiler we will use
CC = g++

# the flags for the compiler 
#-w surpresses all warnings
# COMPILER_FLAGS = -w

#the libraries we're linking against
LINKER_FLAGS = -lsfml-graphics -lsfml-system -lsfml-window

#the name of our executable
OBJ_NAME = main.o

all:
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
