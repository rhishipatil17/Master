SRCDIR= ./src
INCDIRS= -I./include
BUILDDIR= ./build/
TARGET= $(BUILDDIR)/foundationlib.o

CC= g++
LINK= ld
DEPFLAGS= -MP -MD
OPT= -O0
CCFLAGS= -Wall -Wextra -g -fPIC $(INCDIRS) $(OPT) $(DEPFLAGS)
LFLAGS= -r

CPPFILES= $(foreach D,$(SRCDIR),$(wildcard $(D)/*.cpp))
OBJECTS= $(patsubst %.cpp,$(BUILDDIR)%.o,$(CPPFILES))
DEPFILES= $(patsubst %.cpp,$(BUILDDIR)%.d,$(CPPFILES))
BUILDSUBDIR= $(foreach D,$(SRCDIR),$(BUILDDIR)$(D))

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(LINK) $(LFLAGS) $(OBJECTS) -o $(TARGET)

$(BUILDDIR)%.o : %.cpp
	mkdir -p $(BUILDSUBDIR)
	$(CC) $(CCFLAGS) -c $< -o $@

clean: 
	rm -rf $(BUILDDIR)

-include $(DEPFILES)

.PHONY: clean all