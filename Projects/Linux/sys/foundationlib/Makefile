SRCDIR= ./src
INCDIRS= ./include
BUILDDIR= ./build

CODEDIRS= $(SRCDIR)
TARGET= $(BUILDDIR)/foundationlib.o

CC= g++
LINK= ld
DEPFLAGS= -MP -MD
OPT= -O0
CCFLAGS= -Wall -Wextra -std=c++20 -pthread -g -fPIC $(OPT) $(DEPFLAGS) $(foreach D,$(INCDIRS),-I$(D))
LFLAGS= -r

CPPFILES= $(foreach D,$(CODEDIRS),$(wildcard $(D)/*.cpp))
OBJECTS= $(patsubst %.cpp,$(BUILDDIR)/%.o,$(CPPFILES))
DEPFILES= $(patsubst %.cpp,$(BUILDDIR)/%.d,$(CPPFILES))
BUILDSUBDIR= $(foreach D,$(CODEDIRS),$(BUILDDIR)/$(D))

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(LINK) $(LFLAGS) $(OBJECTS) -o $(TARGET)

$(BUILDDIR)/%.o : %.cpp | $(BUILDSUBDIR)
	$(CC) $(CCFLAGS) -c $< -o $@

$(BUILDSUBDIR):
	mkdir -p $(BUILDSUBDIR)

clean: 
	rm -rf $(BUILDDIR)

-include $(DEPFILES)

.PHONY:  all clean