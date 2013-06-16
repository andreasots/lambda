pkgconfig := gl glew 
CXXFLAGS := -std=c++11 $(CXXFLAGS) $(shell pkg-config --cflags $(pkgconfig))
LDFLAGS := $(LDFLAGS) $(shell pkg-config --libs $(pkgconfig)) -lglut
liblambda := ARB_debug_output_callback.o Display.o 

.PHONY: all clean

all: lambda

clean:
	$(RM) lambda *.o

lambda: main.o $(liblambda)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o lambda main.o $(LDFLAGS) $(liblambda)

