# Executable name
TARGET = ring_game_app

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -Iengine -Iring_game

# SFML libraries
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRC = $(wildcard engine/*.cpp) $(wildcard ring_game/*.cpp)

# Object files
OBJ = $(SRC:.cpp=.o)

# Default target
all: $(TARGET)

# Link step (create executable)
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Compilation step (cpp -> object)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJ) $(TARGET)