pkgconfig := gl glew 
CPPFLAGS := -Ijsoncpp
CXXFLAGS := -std=c++11 $(CXXFLAGS) $(shell pkg-config --cflags $(pkgconfig))
LDFLAGS := $(LDFLAGS) $(shell pkg-config --libs $(pkgconfig)) -lglut
liblambda := ARB_debug_output_callback.o Color.o Display.o Scene.o Triangle.o
libjsoncpp := jsoncpp/jsoncpp.o

.PHONY: all clean

all: lambda

clean:
	$(RM) lambda *.o jsoncpp/*.o

lambda: main.o $(liblambda) $(libjsoncpp)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o lambda main.o $(LDFLAGS) $(liblambda) \
		$(libjsoncpp)

