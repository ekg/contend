HEADERS = split.h
SOURCES = split.cpp \
	contend.cpp
OBJECTS= $(SOURCES:.cpp=.o)

BINS = contend

all: $(OBJECTS) $(BINS)

CXX = g++
CXXFLAGS = -O3 -D_FILE_OFFSET_BITS=64
#INCLUDES = -I$(BAMTOOLS_ROOT)/include -Ivcflib/src -Ivcflib/
#LDFLAGS =
#LIBS = -lz -lm -L./ -Lvcflib/tabixpp/ -lbamtools -ltabix

# profiling

profiling:
	$(MAKE) CXXFLAGS="$(CXXFLAGS) -g" all

gprof:
	$(MAKE) CXXFLAGS="$(CXXFLAGS) -pg" all

# libraries

%.o: %.cpp %.h
	$(CXX) -c $(*F).cpp -o $@ $(INCLUDES) $(LDFLAGS) $(CXXFLAGS)

$(BINS): $(OBJECTS) $(SOURCES) $(HEADERS)
	$(CXX) -o $@ $(INCLUDES) $(OBJECTS) $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(BINS) $(OBJECTS)

.PHONY: clean all
