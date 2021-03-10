CXX = g++
CXXFLAGS = -g -std=c++11 -fPIC -Wall
INCS = -I. -Isrc
LIBS = -ldl
LIBS += -lglut -lGL -lGLU -lpthread
SOFLAGS = -DDYNAMIC

SRC_PATH = src/
TANK_PATH = tanks/

TANKS = $(SRC_PATH)SimpleAI.cpp
TANKS += $(SRC_PATH)PongAI.cpp
TANKS += $(SRC_PATH)CamperAI.cpp
TANKS += $(SRC_PATH)StationaryAI.cpp
TANKS += $(SRC_PATH)AttackDownAI.cpp
TANKS += $(SRC_PATH)Turret.cpp
TANKS += $(SRC_PATH)Target.cpp
TANKS += $(SRC_PATH)RecipeAI.cpp
TANKS += $(SRC_PATH)Sentry.cpp

TANKS_LINK = $(SRC_PATH)/Actor.o # need the base class for the .so tank libs


tanks/%.so: $(SRC_PATH)/%.cpp $(TANKS_LINK)
	@mkdir -p tanks
	$(CXX) $(CXXFLAGS) $(INCS) -shared $< $(TANKS_LINK) -o $(TANK_PATH)$(@F) $(SOFLAGS) $(LIBS)

tanks/%.o: $(SRC_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) -c $(INCS) $< $(TANKS_LINK) -o $(TANK_PATH)$(@F).o

all: tanks mapGen mazeGen

tanks: $(TANKS:src/%.cpp=tanks/%.so)

mazeGen: mazeMain.cpp disjointBySize.cpp maze.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS)

mapGen: mapGen.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	@rm -rf $(TEST_PATH)src/*.o
	@rm -rf $(TEST_PATH)*.o
	@rm -rf $(TANK_PATH)/*
	@rm -rf $(SRC_PATH)/*.o
	@rm -rf mapGen

tar:
	tar zcfv Platform.tgz config.ini images src platform mapGen.cpp testTanks.py README Makefile map.txt mazeMain.cpp disjointBySize.{cpp,h} maze.{cpp,h}
	cp Platform.tgz /home/classes/csc340/www/Project/PhaseII
