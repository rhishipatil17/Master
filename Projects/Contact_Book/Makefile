# Compiler
CXX = g++

# Compiler flags
# -Iinclude: Tell the compiler to look for headers in the 'include' directory
# -Wall: Enable all warnings
# -std=c++20: Use the C++20 standard
CXXFLAGS = -Iinclude -Wall -std=c++20

# The name of the executable
TARGET = contact_book.out

# Output directory for object files
ODIR = out

# Source files
SRCS = src/main.cpp src/FileHandler.cpp src/Phonebook.cpp src/PhonebookCli.cpp

# Object files (derived from source files, with output directory)
OBJS = $(patsubst src/%.cpp,$(ODIR)/%.o,$(SRCS))

# The default target: build the executable
all: $(TARGET)

# Rule to link the object files into the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile a .cpp file into a .o file in the output directory
$(ODIR)/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# The clean target: remove generated files and the output directory
clean:
	rm -rf $(ODIR) $(TARGET)

.PHONY: all clean
