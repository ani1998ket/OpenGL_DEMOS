CC := g++
OPTIONS := -Wall
SRCPATH := ../src
DEPENDS := $(SRCPATH)/Window.cpp
LIBS := -lglfw -lGL -lGLEW

% : %.cpp
	$(CC) $(OPTIONS) -I $(SRCPATH) $(DEPENDS)  $< $(LIBS) -o bin_$@ 

clean :
	rm bin_*