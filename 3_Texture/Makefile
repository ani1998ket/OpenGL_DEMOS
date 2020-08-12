CC := g++
OPTIONS := 
INCPATH := -I ../src -I ../vendor
SRCPATH := ../src
DEPENDS := $(SRCPATH)/Window.cpp $(SRCPATH)/GL_Objects.cpp
LIBS := -lglfw -lGL -lGLEW

% : %.cpp
	$(CC) $(OPTIONS) $(INCPATH) $(DEPENDS)  $< $(LIBS) -o $@ 

clean :
	rm bin_*