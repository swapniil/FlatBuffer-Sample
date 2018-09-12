CC := g++
SRCDIR := src
BUILDDIR := build
TARGET := flatbuffer-demo-app
  
SRCEXT := cc
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -Wall -std=c++11 -O3 -fPIC -Ofast -m64 -march=native -g
LIB := -pthread -L lib -L /usr/local/lib
INC := -I fbs_source -I /usr/local/include -I ../../include

$(TARGET): $(OBJECTS)
	  @echo " Linking..."
	    @echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

DEPS := $(OBJECTS:.o=.d)

-include $(DEPS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)

	  @mkdir -p $(BUILDDIR)
	    @echo "flatc  --cpp -o src/ ./fbs_schema/*.fbs"; flatc --cpp -o src/ ./fbs_schema/*.fbs; echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) -MMD -MF $(patsubst %.o,%.d,$@) $(INC) -c -o $@ $<

clean:
	  @echo " Cleaning...";
	  @echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET);echo "$(RM) -f src/*_generated.h"; $(RM) -f src/*_generated.h
	    @echo " find ./ -name build_stats.cc | xargs $(RM)"; find ./ -name build_stats.cc | xargs $(RM)

.PHONY: clean
