#
# Birthday tests
#

# Define compiler
CXX = $(shell fltk-config --cxx)

# Set compiler flags
# CXXFLAGS = $(shell fltk-config --cxxflags) -std=c++14
CXXFLAGS = -std=c++14

# Library link
# LINK_FLTK = $(shell fltk-config --ldstaticflags)
LINK_DATE_TIME = -lboost_date_time

# Directory Access
SRC = ../../src

# Define what target application is called
all: Tests

# Define how to build the object files
tests-main.o: tests-main.cpp ../lib/catch.hpp
	$(CXX) -c $< $(CXXFLAGS)
tests-date_time_ext.o: tests-date_time_ext.cpp $(SRC)/date_time_ext.hpp
	$(CXX) -c $< $(CXXFLAGS)

# Linkage
Tests: tests-main.o tests-date_time_ext.o
	$(CXX) -o $@ tests-main.o tests-date_time_ext.o $(LINK_DATE_TIME)

.PHONY: clean

clean:
	rm Tests *.o
