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
OBJECTS = main.o Birthday_win.o Window.o Shape.o Widget.o Fl_Justify_Input.o

# Define what target application is called
all: Birthday

# Define how to build the object files
main.o: Birthday_win.hpp
Birthday_win.o: Birthday_win.hpp ./gui/Window.hpp ./gui/Widget.hpp \
	./gui/Shape.hpp date_time_ext.hpp

# Really need to bust these out into a local lib
Fl_Justify_Input.o: ./gui/Fl_Justify_Input.cpp
	$(CXX) -c $< $(CXXFLAGS)
Window.o: ./gui/Window.cpp ./gui/Window.hpp ./gui/Shape.hpp
	$(CXX) -c $< $(CXXFLAGS)
Shape.o: ./gui/Shape.cpp ./gui/Shape.hpp
	$(CXX) -c $< $(CXXFLAGS)
Widget.o: ./gui/Widget.cpp ./gui/Widget.hpp ./gui/Fl_Justify_Input.hpp
	$(CXX) -c $< $(CXXFLAGS)

# Define how to link final app
Birthday: $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LINK_FLTK) $(LINK_DATE_TIME)

.PHONY: clean
clean:
	rm Birthday *.o
