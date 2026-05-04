# Executable name
TARGET = ring_game_app

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -Iengine -Iring_game -MMD -MP

# SFML libraries
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRC = $(wildcard engine/*.cpp) $(wildcard ring_game/*.cpp)

# Object files
OBJ = $(SRC:.cpp=.o)

# Dependency files
DEP = $(OBJ:.o=.d)

# Default target
all: $(TARGET)

# Link step
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Compilation step
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include generated dependency files
-include $(DEP)

# Clean build files
clean:
	rm -f $(OBJ) $(DEP) $(TARGET)

.PHONY: all clean