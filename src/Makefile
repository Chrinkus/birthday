#
# Birthday Makefile
#

# Define compiler
CXX = $(shell fltk-config --cxx)

# Set compiler flags
CXXFLAGS = $(shell fltk-config --cxxflags) -std=c++14

# Library link
LINK_FLTK = $(shell fltk-config --ldstaticflags)
LINK_DATE_TIME = -lboost_date_time

# List of Object files
OBJECTS = main.o Birthday_win.o Widget_factory.o Window.o Shape.o Widget.o

# Define what target application is called
all: Birthday

# Define how to build the object files
main.o: Birthday_win.hpp
Widget_factory.o: Widget_factory.hpp ./gui/Window.hpp ./gui/Widget.hpp
Birthday_win.o: Birthday_win.hpp ./gui/Window.hpp Widget_factory.hpp\
	./gui/Shape.hpp date_time_ext.hpp Color_scheme.hpp

# Really need to bust these out into a local lib
Window.o: ./gui/Window.cpp ./gui/Window.hpp ./gui/Shape.hpp
	$(CXX) -c $< $(CXXFLAGS)
Shape.o: ./gui/Shape.cpp ./gui/Shape.hpp
	$(CXX) -c $< $(CXXFLAGS)
Widget.o: ./gui/Widget.cpp ./gui/Widget.hpp
	$(CXX) -c $< $(CXXFLAGS)

# Define how to link final app
Birthday: $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LINK_FLTK) $(LINK_DATE_TIME)

.PHONY: clean
clean:
	rm Birthday *.o
