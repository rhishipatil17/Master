FOUNDATIONLIB = ../../foundationlib
SRCDIR= ./src
INCDIR= ./include
BUILDDIR= ./build
CODEDIRS= $(SRCDIR)

DEPDIR= $(FOUNDATIONLIB)
DEPINCDIR= $(FOUNDATIONLIB)/include
DEPOBJDIR= $(foreach D,$(DEPDIR),$(D)/build)
DEPOBJECTS= $(foreach D,$(DEPOBJDIR),$(D)/*.o)

TARGET= $(BUILDDIR)/startup.o
FINALTARGET= $(BUILDDIR)/startup.out

CC= g++
LINK= ld
DEPFLAGS=-MP -MD
OPT= -O0
CCFLAGS=-Wall -Wextra -g -fPIC  $(OPT) $(DEPFLAGS) $(foreach D,$(INCDIR),-I$(D)) $(foreach D,$(DEPINCDIR),-I$(D))
LFLAGS= -r

BUILDSUBDIR= $(foreach D,$(CODEDIRS),$(BUILDDIR)/$(D))
CPPFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.cpp))
OBJECTS=$(patsubst %.cpp,$(BUILDDIR)/%.o,$(CPPFILES))
DEPFILES=$(patsubst %.cpp,$(BUILDDIR)/%.d,$(CPPFILES))

all: $(TARGET) $(FINALTARGET)

$(FINALTARGET): 
	for dir in $(DEPDIR); do \
        make -C $$dir all; \
    done

	mkdir $(BUILDDIR)/tmp
	cp $(DEPOBJECTS) $(BUILDDIR)/tmp

	$(CC) $(BUILDDIR)/*.o $(BUILDDIR)/tmp/*.o -o $(FINALTARGET)

	rm -rf $(BUILDDIR)/tmp

$(TARGET) : $(OBJECTS)
	$(LINK) $(LFLAGS) $(OBJECTS) -o $(TARGET)

$(BUILDDIR)/%.o : %.cpp | $(BUILDSUBDIR)
	$(CC) $(CCFLAGS) -c $< -o $@

$(BUILDSUBDIR):
	mkdir -p $(BUILDSUBDIR)

clean:
	rm -rf $(BUILDDIR)/

cleanall:
	for dir in $(DEPDIR); do \
        make -C $$dir clean; \
    done
	rm -rf $(BUILDDIR)

-include $(DEPFILES)

.PHONY: all clean cleanall