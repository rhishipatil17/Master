CC= g++
OPT= -O0

FOUNDATIONLIB = ../../foundationlib
SRCDIR= ./src
INCDIRS= ./include $(FOUNDATIONLIB)/include
BUILDDIR= ./build

TARGET= startup
CODEDIRS= $(SRCDIR) $(FOUNDATIONLIB)/src

DEPFLAGS=-MP -MD
CCFLAGS=-Wall -Wextra -g $(foreach D,$(INCDIRS),-I$(D)) $(OPT) $(DEPFLAGS)

CPPFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.cpp))
OBJECTS=$(patsubst %.cpp,%.o,$(CPPFILES))
DEPFILES=$(patsubst %.cpp,%.d,$(CPPFILES))

all: $(TARGET)
#	@echo $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

%.o : %.cpp
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	rm -rf $(TARGET) $(OBJECTS) $(DEPFILES)

-include $(DEPFILES)

.PHONY: all clean distribute diff