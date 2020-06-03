CXX := g++
CXXFLAGS := --std=c++11 -g -Wall
INC := -I include
# using SFML version 2.4.2
SFML_INCLUDE := -DSFML_STATIC -I "D:/Program Files (x86)/SFML/include"
SFML_LIB := -L "D:/Program Files (x86)/SFML/lib" \
	-l sfml-graphics-s-d \
	-l sfml-window-s-d \
	-l sfml-system-s-d \
	-l opengl32 \
	-l winmm \
	-l gdi32 \
	-l freetype \
	-l jpeg \

build/mazeHelper.o: mazeHelper.cpp mazeHelper.h
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INC) $(SFML_INCLUDE)

#kruskall: bin/kruskall
#
#bin/kruskall: build/kruskall.o build/mazeHelper.o
#	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIB)
#
#build/kruskall.o: kruskall.cpp mazeHelper.h
#	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INC) $(SFML_INCLUDE)

prim: bin/prim

bin/prim: build/prim.o build/mazeHelper.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIB)

build/prim.o: prim.cpp mazeHelper.h
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INC) $(SFML_INCLUDE)

clean:
	rm build/*.*
