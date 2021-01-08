CXX = g++
CXXFLAGS = -std=c++17 -fPIC -g -Iinclude/ -I../include/
LDFLAGS = -shared
LIBS = -lpthread

TARGET  = libprofiler_adapter.so
SOURCES = source/profiler.cpp
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

clean:
	rm -f ${TARGET}
