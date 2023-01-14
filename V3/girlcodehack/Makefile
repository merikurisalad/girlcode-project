EXE = pa2
TESTCLOTHINGOVERLAY = testClothingOverlay

OBJS_EXE = RGBAPixel.o lodepng.o PNG.o  main.o clothingoverlay.o
OBJS_M = RGBAPixel.o lodepng.o PNG.o clothingoverlay.o testClothingOverlay.o

CXX = clang++
CXXFLAGS = -std=c++14 -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
#LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread -lm
LDFLAGS = -std=c++14 -lpthread -lm

all : $(EXE) $(TESTCLOTHINGOVERLAY)

$(EXE) : $(OBJS_EXE)
	$(LD) $(OBJS_EXE) $(LDFLAGS) -o $(EXE)

$(TESTCLOTHINGOVERLAY) : $(OBJS_M)
	$(LD) $(OBJS_M) $(LDFLAGS) -o $(TESTCLOTHINGOVERLAY)

#object files

testClothingOverlay.o : testClothingOverlay.cpp cs221util/PNG.h cs221util/RGBAPixel.h clothingoverlay.h clothingoverlay.cpp
	$(CXX) $(CXXFLAGS) testClothingOverlay.cpp

clothingoverlay.o : clothingoverlay.cpp cs221util/PNG.h cs221util/RGBAPixel.h clothingoverlay.h clothingoverlay.cpp
	$(CXX) $(CXXFLAGS) clothingoverlay.cpp

RGBAPixel.o : cs221util/RGBAPixel.cpp cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/RGBAPixel.cpp -o $@

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/RGBAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp -o $@

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp -o $@

main.o : main.cpp cs221util/PNG.h cs221util/RGBAPixel.h 
	$(CXX) $(CXXFLAGS) main.cpp -o $@

clean :
	-rm -f *.o $(EXE)
