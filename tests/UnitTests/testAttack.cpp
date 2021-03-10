#include "catch.hpp"
#include "../../src/RecipeAI.h"
#include <iostream>
#include "defines.h"

// The map.map object being tested
// 1 0 0
// 0 0 0
// 0 0 2

TEST_CASE("If threats detected DOWNRIGHT, attack direction should be DOWNRIGHT")
{
   RecipeAI recipeai;
   MapData map(MapSizeX,MapSizeY);
   map.map[MapSizeX*(MapSizeY-1)+MapSizeX-1] = OpponentID;
   PositionData status(MyID,MyHealth,MyXPos,MyYPos,1,1);
   attributes baseStats(2,2,2,2,2,5,5);
	recipeai.setAttribute(0, baseStats);

   REQUIRE(recipeai.spendAP(map, status) == 2);
   REQUIRE(recipeai.attack(map, status) == DOWNRIGHT);
}

// The map.map object being tested
// 1 0 0 0
// 0 0 0 0
// 0 0 0 0
// 0 0 2 0

TEST_CASE("If threats detected are not attackable, should return STAY")
{
   RecipeAI recipeai;
   MapData map(MapSizeX+1,MapSizeY+1);
   map.map[MapSizeX*(MapSizeY-1)+MapSizeX-2] = OpponentID;
   PositionData status(MyID,MyHealth,MyXPos,MyYPos,1,1);
   attributes baseStats(2,2,2,2,2,5,5);
	recipeai.setAttribute(0, baseStats);

   REQUIRE(recipeai.spendAP(map, status) != 2);
   REQUIRE(recipeai.attack(map, status) == STAY);
}

// The map.map object being tested
// 1 0 0 0
// 0 0 0 0
// 0 0 0 0
// 2 0 3 0

TEST_CASE("If there are multiple threats, attack the one on a shot line")
{
   RecipeAI recipeai;
   MapData map(MapSizeX+1,MapSizeY+1);
   map.map[3*(MapSizeX+1)] = OpponentID;
   map.map[3*(MapSizeX+1)+2] = OpponentID+1;
   PositionData status(MyID,MyHealth,MyXPos,MyYPos,1,1);
   attributes baseStats(2,2,2,2,2,5,5);
	recipeai.setAttribute(0, baseStats);

   REQUIRE(recipeai.spendAP(map, status) == 2);
   REQUIRE(recipeai.attack(map, status) == DOWN);
}

// The map.map object being tested
// 1 0 0 0
// 0 0 0 0
// 0 3 0 0
// 0 0 0 2

TEST_CASE("If there are multiple threats, attack the one on a shot lineII")
{
   RecipeAI recipeai;
   MapData map(MapSizeX+1,MapSizeY+1);
   map.map[3*(MapSizeX+1)+3] = OpponentID;
   map.map[2*(MapSizeX+1)+1] = OpponentID+1;
   PositionData status(MyID,MyHealth,MyXPos,MyYPos,1,1);
   attributes baseStats(2,2,2,2,2,5,5);
	recipeai.setAttribute(0, baseStats);

   REQUIRE(recipeai.spendAP(map, status) == 2);
   REQUIRE(recipeai.attack(map, status) == DOWNRIGHT);
}

// The map.map object being tested
// 1 R 2
// 0 0 0
// 0 0 0

TEST_CASE("If there is an obstacle in the way, do not shoot")
{
   RecipeAI recipeai;
   MapData map(MapSizeX,MapSizeY);
   map.map[2] = OpponentID;
   map.obstacleMap[1] = 82;
   PositionData status(MyID,MyHealth,MyXPos,MyYPos,1,1);
   attributes baseStats(2,2,2,2,2,5,5);
	recipeai.setAttribute(0, baseStats);

   REQUIRE(recipeai.spendAP(map, status) != 2);
   REQUIRE(recipeai.attack(map, status) == STAY);
}
