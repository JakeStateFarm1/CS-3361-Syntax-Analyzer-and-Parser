# Makefile for compiling a C program with calculator.c and main.c

# Compiler settings - Can be changed to clang++, etc.
CXX = gcc
# Compiler flags, -Wall for all warnings, -g for debugging information
CXXFLAGS = -Wall -g

# Name of the target executable
TARGET = cooke_parser

# List of object files to be compiled
OBJS = front.o parser.o

# Link the object files to create the executable
# $@ represents the target, $(OBJS) are the prerequisites
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compile front.c into front.o
# $@ is the target (main.o), $< is the first prerequisite (front.c)
front.o: front.c front.h
	$(CXX) $(CXXFLAGS) -c $<

# Compile parser.c into parser.o
# $@ is the target (parser.o), $< is the first prerequisite (parser.c)
parser.o: parser.c parser.h
	$(CXX) $(CXXFLAGS) -c $<


# Clean target for removing compiled files
# A phony target because it doesn't represent a file
.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)

