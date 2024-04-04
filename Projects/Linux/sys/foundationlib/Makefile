TARGET= foundationlib.o
SRCDIR= ./src
INCDIRS= -I./include
BUILDDIR= ./build/

CC= g++
LINK= ld
DEPFLAGS= -MP -MD
OPT= -O0
CCFLAGS= -Wall -Wextra -g -fPIC $(INCDIRS) $(OPT) $(DEPFLAGS)
LFLAGS= -r

CPPFILES= $(foreach D,$(SRCDIR),$(wildcard $(D)/*.cpp))
OBJECTS= $(patsubst %.cpp,%.o,$(CPPFILES))
DEPFILES= $(patsubst %.cpp,%.d,$(CPPFILES))
BUILDSUBDIR= $(foreach D,$(SRCDIR),$(BUILDDIR)$(D))

all : $(TARGET)
	mkdir -p $(BUILDSUBDIR)
	mv $(OBJECTS) $(BUILDDIR)$(OBJECTS)
	mv $(DEPFILES) $(BUILDDIR)$(DEPFILES)
	mv $(TARGET) $(BUILDDIR)

$(TARGET) : $(OBJECTS)
	$(LINK) $(LFLAGS) $(OBJECTS) -o $(TARGET)

%.o : %.cpp
	$(CC) $(CCFLAGS) -c -o $@ $<

clean: 
	rm -rf $(BUILDDIR)

-include $(DEPFILES)

.PHONY: clean