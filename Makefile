#This is the makeFile for all the source files
# g++ -o final memoryManager.cpp mapTask.cpp singleLevelTask.cpp twoLevelTask.cpp performanceModule.cpp inputOutputManager.cpp final.cpp

# $(CC) = g++

# final: &(CC) -o final memoryManager.cpp mapTask.cpp singleLevelTask.cpp twoLevelTask.cpp performanceModule.cpp inputOutputManager.cpp final.cpp

# clean: rm *.o final

# Makefile for compiling the project with g++

# Compiler
CXX = g++

# Compiler flags
# CXXFLAGS = -Wextra -O2

# Output executable name
TARGET = final

# Source files
SRC = memoryManager.cpp \
      mapTask.cpp \
      singleLevelTask.cpp \
      twoLevelTask.cpp \
      performanceModule.cpp \
      inputOutputManager.cpp \
      final.cpp

# Object files (replace .cpp with .o for each source file)
OBJ = $(SRC:.cpp=.o)

# Default target
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ)

# Compiling source files into object files
%.o: %.cpp
	$(CXX) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets
.PHONY: all clean
