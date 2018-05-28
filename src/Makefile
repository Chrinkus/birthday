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

# Define what target application is called
all: Birthday

# Define how to build the object files
main.o: main.cpp Prompt_window.hpp
	$(CXX) -c $< $(CXXFLAGS)
Prompt_window.o: Prompt_window.cpp Prompt_window.hpp ../gui/Window.hpp ../gui/Widget.hpp ../gui/Shape.hpp date_time_ext.hpp
	$(CXX) -c $< $(CXXFLAGS)
Window.o: ../gui/Window.cpp ../gui/Window.hpp ../gui/Shape.hpp
	$(CXX) -c $< $(CXXFLAGS)
Shape.o: ../gui/Shape.cpp ../gui/Shape.hpp
	$(CXX) -c $< $(CXXFLAGS)
Widget.o: ../gui/Widget.cpp ../gui/Widget.hpp
	$(CXX) -c $< $(CXXFLAGS)

# Define how to link final app
Birthday: main.o Prompt_window.o Window.o Shape.o Widget.o
	$(CXX) -o $@ main.o Prompt_window.o Window.o Shape.o Widget.o $(LINK_FLTK) $(LINK_DATE_TIME)

.PHONY: clean
clean:
	rm Birthday *.o
