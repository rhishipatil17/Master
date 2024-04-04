TARGET= foundationlib.o
SRCDIR= ./src
INCDIRS= -I./include

CC= g++
LINK= ld
DEPFLAGS= -MP -MD
OPT= -O0
CCFLAGS= -Wall -Wextra -g -fPIC $(INCDIRS) $(OPT) $(DEPFLAGS)
LFLAGS= -r

CPPFILES=$(foreach D,$(SRCDIR),$(wildcard $(D)/*.cpp))
OBJECTS=$(patsubst %.cpp,%.o,$(CPPFILES))
DEPFILES=$(patsubst %.cpp,%.d,$(CPPFILES))

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(LINK) $(LFLAGS) $(OBJECTS) -o $(TARGET)

%.o : %.cpp
	$(CC) $(CCFLAGS) -c -o $@ $<

clean: 
	rm $(OBJECTS) $(DEPFILES) $(TARGET)

-include $(DEPFILES)

.PHONY: clean