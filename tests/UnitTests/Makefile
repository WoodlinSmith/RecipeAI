SRC_PATH = ../../src/


SRC = testMain.cpp \
      testSetAttributes.cpp \
      testSpendAP.cpp \
      testAttack.cpp \
      testMove.cpp \
      $(SRC_PATH)RecipeAI.cpp \
      $(SRC_PATH)Actor.cpp

OBJS = $(SRC:%.cpp=%.o)

OBJS += MapData.o

CXXFLAGS = -std=c++11 -g
CXX = g++

LIBS =

VPATH = ../src

INC = -I../src

all: testMain

testMain: $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

MapData.o: MapData.cpp
	$(CXX) -c -o $@ $^ $(CXXFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) -c -o $@ $^ $(CXXFLAGS) $(INC)

clean:
	rm -rf *.o
	rm -rf testMain
	rm -rf $(SRC_PATH)*.o
