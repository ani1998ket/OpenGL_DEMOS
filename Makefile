CC := g++
OPTIONS := -Wall
SRCPATH := -I src -I vendor
DEPENDS := $(SRCPATH)/Window.cpp $(SRCPATH)/GL_Objects.cpp
LIBS := -lglfw -lGL -lGLEW

% : %.cpp
	$(CC) $(OPTIONS) $(SRCPATH) $(DEPENDS)  $< $(LIBS) -o bin_$@ 

clean :
	rm bin_*