#include "catch.hpp"
#include "../../src/RecipeAI.h"
#include <iostream>
#include "defines.h"

// Under no circumstance should the recipeai move

TEST_CASE("RecipeAI will wander the map looking for tanks if none are present")
{
   RecipeAI recipeai;
   MapData map(MapSizeX,MapSizeY);
   PositionData status(MyID,MyHealth,MyXPos,MyYPos,1,1);
   attributes baseStats(2,2,2,2,2,5,5);
	recipeai.setAttribute(0, baseStats);

   REQUIRE(recipeai.spendAP(map, status) == 1);
   REQUIRE(recipeai.move(map, status) != STAY);
}

// The map.map object being tested
// 1 0 0 0
// 0 0 0 0
// 0 0 0 0
// 0 0 2 0
TEST_CASE("RecipeAI is almost diagonal, should move into line of sight")
{
	RecipeAI recipeai;
	MapData map(MapSizeX+1,MapSizeX+1);
   map.map[3*(MapSizeX+1)+2] = OpponentID;
   PositionData status(MyID,MyHealth,MyXPos,MyYPos,1,1);
   attributes baseStats(2,2,2,2,2,5,5);
	recipeai.setAttribute(0, baseStats);

   REQUIRE(recipeai.spendAP(map, status) == 1);
   REQUIRE(recipeai.move(map, status) == DOWN);
}

// The map.map object being tested
// 1 0 0
// 0 0 0
// 0 0 2
TEST_CASE("RecipeAI only has 1 AP, so tank should move out of the line of sight and trigger safemode")
{
	RecipeAI recipeai;
	MapData map(MapSizeX,MapSizeX);
   map.map[2*(MapSizeX)+2] = OpponentID;
   PositionData status(MyID,MyHealth,MyXPos,MyYPos,1,1);
   attributes baseStats(1,1,1,1,1,5,5);
	recipeai.setAttribute(0, baseStats);

   REQUIRE(recipeai.spendAP(map, status) == 1);
   REQUIRE(recipeai.move(map, status) == RIGHT);
}

// The map.map object being tested
// 1 R 2
// 0 0 0
// 0 0 0
TEST_CASE("RecipeAI moving around an obstacle to target another tank")
{
	RecipeAI recipeai;
	MapData map(MapSizeX,MapSizeX);
   map.map[2] = OpponentID;
   map.obstacleMap[1] = 82;
   PositionData status(MyID,MyHealth,MyXPos,MyYPos,2,2);
   attributes baseStats(3,3,3,3,3,5,5);
	recipeai.setAttribute(0, baseStats);

   REQUIRE(recipeai.spendAP(map, status) == 1);
   REQUIRE(recipeai.move(map, status) == DOWN);
}

// The map.map object being tested
// 1 R 2
// 0 0 0
// 0 0 0
TEST_CASE("RecipeAI is in safemode so will not move into the line of sight")
{
	RecipeAI recipeai;
	MapData map(MapSizeX,MapSizeX);
   map.map[2] = OpponentID;
   map.obstacleMap[1] = 82;
   PositionData status(MyID,MyHealth,MyXPos,MyYPos,1,1);
   attributes baseStats(1,1,1,1,1,5,5);
	recipeai.setAttribute(0, baseStats);

   REQUIRE(recipeai.spendAP(map, status) != 1);
   REQUIRE(recipeai.move(map, status) == STAY);
}

// 1 0 0 0
// 0 0 0 2
// 0 0 0 0
// 0 0 0 0
//TEST_CASE("RecipeAI moves into the line of sight")
//TEST_CASE(moving around the map generally)
//TEST_CASE()
